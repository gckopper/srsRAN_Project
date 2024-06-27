/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * This file is part of srsRAN.
 *
 * srsRAN is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsRAN is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

#include "du_ue_ric_configuration_procedure.h"
#include "srsran/ran/resource_block.h"
#include "srsran/ran/s_nssai.h"
#include "srsran/support/async/execute_on.h"
#include <cassert>
#include <vector>

using namespace srsran;
using namespace srs_du;

du_ue_ric_configuration_procedure::du_ue_ric_configuration_procedure(const du_mac_sched_control_config& request_,
                                                                     du_ue_manager_repository&          ue_mng_,
                                                                     const du_manager_params&           du_params_) :
  logger(srslog::fetch_basic_logger("DU-RIC")), request(request_), ue_mng(ue_mng_), du_params(du_params_)
{
}

void du_ue_ric_configuration_procedure::operator()(coro_context<async_task<du_mac_sched_control_config_response>>& ctx)
{
  CORO_BEGIN(ctx);

  // Change execution context to DU manager.
  CORO_AWAIT(execute_on_blocking(du_params.services.du_mng_exec));

  // Run config task inside the UE task loop and await for its completion.
  CORO_AWAIT(dispatch_ue_config_task());

  // TODO: Potentially change back to caller execution context.

  CORO_RETURN(ue_config_completed.get());
}

manual_event<du_mac_sched_control_config_response>& du_ue_ric_configuration_procedure::dispatch_ue_config_task()
{
  // Start as failed and change it if needed
  du_mac_sched_control_config_response fail{false, false, false};
  // TODO go through all parameters
  s_nssai_t  requested_nssai = request.param_list[0].rrm_policy_group->pol_member.s_nssai;
  const auto filter          = [requested_nssai](const du_ue* test_ue) {
    if (test_ue->bearers.drbs().empty()) {
      return false;
    }
    s_nssai_t ue_nssai = test_ue->bearers.drbs().begin()->second->s_nssai;
    if (ue_nssai.sst != requested_nssai.sst) {
      return false;
    }
    if (!(ue_nssai.sd.has_value() && requested_nssai.sd.has_value())) {
      return false;
    }
    if (ue_nssai.sd.value() != requested_nssai.sd.value()) {
      return false;
    }
    return true;
  };
  std::vector<du_ue*> ues = ue_mng.find_ues(filter);
  if (ues.empty()) {
    ue_config_completed.set(fail);
    return ue_config_completed;
  }
  logger.debug(
      "{} UEs were found for SST {} and SD {}", ues.size(), requested_nssai.sst, requested_nssai.sd.value_or(0));

  for (du_ue* test_ue : ues) {
    // Dispatch UE configuration to UE task loop inside the UE manager.
    ue_mng.schedule_async_task(test_ue->ue_index, launch_async([this, test_ue](coro_context<async_task<void>>& ctx) {
                                 CORO_BEGIN(ctx);

                                 // Await for UE configuration completion.
                                 // TODO Find a way to efficiently merge all results
                                 // CORO_AWAIT_VALUE(const mac_ue_reconfiguration_response result,
                                 // handle_mac_config(test_ue));
                                 CORO_AWAIT(handle_mac_config(test_ue));

                                 // TODO Signal completion of UE configuration to external coroutine.

                                 CORO_RETURN();
                               }));
  }

  // TODO always returns true
  ue_config_completed.set(du_mac_sched_control_config_response({true, true, true}));
  logger.info("ue reconfiguration completed with {}", true);

  return ue_config_completed;
}

async_task<mac_ue_reconfiguration_response> du_ue_ric_configuration_procedure::handle_mac_config(du_ue* test_ue)
{
  mac_ue_reconfiguration_request mac_request;

  mac_request.ue_index    = test_ue->ue_index;
  mac_request.crnti       = test_ue->rnti;
  mac_request.pcell_index = to_du_cell_index(0);

  // Configure UE resource allocation parameters.
  mac_request.sched_cfg.res_alloc_cfg.emplace();
  auto& res_alloc_cfg = mac_request.sched_cfg.res_alloc_cfg.value();
  // For now take first parameter set, in future we will have to support multiple parameter sets for different slices.
  control_config_params  req     = request.param_list[0];
  rrm_policy_ratio_group dummy   = {};
  res_alloc_cfg.rrm_policy_group = req.rrm_policy_group.has_value() ? req.rrm_policy_group.value() : dummy;
  // TODO remove when RRM group support is added to scheduler.
  res_alloc_cfg.pdsch_grant_size_limits = {
      req.rrm_policy_group.has_value() ? (req.rrm_policy_group.value().min_prb_policy_ratio.has_value()
                                              ? req.rrm_policy_group.value().min_prb_policy_ratio.value()
                                              : 0)
                                       : 0,
      req.rrm_policy_group.has_value() ? (req.rrm_policy_group.value().max_prb_policy_ratio.has_value()
                                              ? req.rrm_policy_group.value().max_prb_policy_ratio.value()
                                              : MAX_NOF_PRBS)
                                       : MAX_NOF_PRBS};

  res_alloc_cfg.max_pdsch_harq_retxs = req.num_harq_retransmissions.has_value()
                                           ? req.num_harq_retransmissions.value()
                                           : du_params.mac.sched_cfg.ue.max_nof_harq_retxs;
  res_alloc_cfg.max_pusch_harq_retxs = res_alloc_cfg.max_pdsch_harq_retxs;
  logger.info("Setting the PRBs for {} as [{}, {}]",
              mac_request.crnti,
              res_alloc_cfg.pdsch_grant_size_limits.start(),
              res_alloc_cfg.pdsch_grant_size_limits.stop());

  return du_params.mac.ue_cfg.handle_ue_reconfiguration_request(mac_request);
}
