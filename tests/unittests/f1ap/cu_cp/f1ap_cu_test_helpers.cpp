/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "f1ap_cu_test_helpers.h"
#include "srsran/asn1/f1ap/f1ap_pdu_contents_ue.h"
#include "srsran/cu_cp/cu_cp_types.h"
#include "srsran/ran/five_qi.h"
#include "srsran/ran/nr_cgi.h"
#include "srsran/support/async/async_test_utils.h"
#include "srsran/support/test_utils.h"

using namespace srsran;
using namespace srs_cu_cp;

gnb_cu_ue_f1ap_id_t srsran::srs_cu_cp::generate_random_gnb_cu_ue_f1ap_id()
{
  return int_to_gnb_cu_ue_f1ap_id(test_rgen::uniform_int<uint64_t>(
      gnb_cu_ue_f1ap_id_to_uint(gnb_cu_ue_f1ap_id_t::min), gnb_cu_ue_f1ap_id_to_uint(gnb_cu_ue_f1ap_id_t::max) - 1));
}

f1ap_cu_test::f1ap_cu_test(const f1ap_configuration& f1ap_cfg)
{
  test_logger.set_level(srslog::basic_levels::debug);
  f1ap_logger.set_level(srslog::basic_levels::debug);
  srslog::init();

  // We enable Json logging by default for the purpose of testing.
  f1ap_configuration tmp = f1ap_cfg;
  tmp.json_log_enabled   = true;

  f1ap = create_f1ap(tmp, f1ap_pdu_notifier, du_processor_notifier, timers, ctrl_worker);
}

f1ap_cu_test::~f1ap_cu_test()
{
  // flush logger after each test
  srslog::flush();
}

f1ap_cu_test::test_ue& f1ap_cu_test::create_ue(gnb_du_ue_f1ap_id_t du_ue_id)
{
  f1ap_message msg = generate_init_ul_rrc_message_transfer(
      du_ue_id, to_rnti(0x4601), byte_buffer::create({0x1, 0x2, 0x3, 0x4}).value());
  f1ap->handle_message(msg);
  ue_index_t ue_index = *du_processor_notifier.last_created_ue_index;
  test_ues.emplace(ue_index, test_ue{ue_index});
  test_ues[ue_index].ue_index = ue_index;
  test_ues[ue_index].du_ue_id = du_ue_id;
  return test_ues[ue_index];
}

f1ap_cu_test::test_ue& f1ap_cu_test::run_ue_context_setup()
{
  f1ap_ue_context_setup_request req = create_ue_context_setup_request({});

  // Start procedure in CU.
  async_task<f1ap_ue_context_setup_response>         t = f1ap->handle_ue_context_setup_request(req, {});
  lazy_task_launcher<f1ap_ue_context_setup_response> t_launcher(t);

  // Take allocated CU ID from UE context setup request.
  gnb_cu_ue_f1ap_id_t cu_ue_id = int_to_gnb_cu_ue_f1ap_id(
      this->f1ap_pdu_notifier.last_f1ap_msg.pdu.init_msg().value.ue_context_setup_request()->gnb_cu_ue_f1ap_id);

  // Generate random DU ID
  gnb_du_ue_f1ap_id_t du_ue_id = int_to_gnb_du_ue_f1ap_id(test_rgen::uniform_int<uint32_t>());

  // Handle response from DU.
  f1ap_message response = generate_ue_context_setup_response(cu_ue_id, du_ue_id);
  f1ap->handle_message(response);

  srsran_assert(t.ready(), "The procedure should have completed by now");

  // Create test UE using identifiers allocated from precedure.
  ue_index_t ue_index = t.get().ue_index;
  test_ues.emplace(ue_index, test_ue{ue_index});
  test_ues[ue_index].ue_index = ue_index;
  test_ues[ue_index].cu_ue_id = cu_ue_id;
  test_ues[ue_index].du_ue_id = du_ue_id;
  return test_ues[ue_index];
}

void f1ap_cu_test::tick()
{
  this->timers.tick();
  this->ctrl_worker.run_pending_tasks();
}

f1ap_ue_context_setup_request
srsran::srs_cu_cp::create_ue_context_setup_request(const std::initializer_list<drb_id_t>& drbs_to_add)
{
  f1ap_ue_context_setup_request req;

  req.ue_index = uint_to_ue_index(19);

  // sp cell id
  req.sp_cell_id.nci      = 6576;
  req.sp_cell_id.plmn_hex = "00f110";

  // serv cell idx
  req.serv_cell_idx = 1;

  // cu to du to rrc info
  req.cu_to_du_rrc_info.cg_cfg_info               = make_byte_buffer("deadbeef");
  req.cu_to_du_rrc_info.ue_cap_rat_container_list = make_byte_buffer("deadbeef");
  req.cu_to_du_rrc_info.meas_cfg                  = make_byte_buffer("deadbeef");

  // drx cycle
  f1ap_drx_cycle drx_cycle;
  drx_cycle.long_drx_cycle_len    = 5;
  drx_cycle.short_drx_cycle_len   = 1;
  drx_cycle.short_drx_cycle_timer = 10;
  req.drx_cycle                   = drx_cycle;

  for (const auto& drb : drbs_to_add) {
    f1ap_drbs_to_be_setup_mod_item drb_item;
    drb_item.drb_id = drb;
    drb_item.qos_info.drb_qos.qos_characteristics.non_dyn_5qi.emplace();
    drb_item.qos_info.drb_qos.qos_characteristics.non_dyn_5qi.value().five_qi    = five_qi_t::min;
    drb_item.qos_info.drb_qos.alloc_and_retention_prio.prio_level_arp            = 0;
    drb_item.qos_info.drb_qos.alloc_and_retention_prio.pre_emption_cap           = "shall_not_trigger_pre_emption";
    drb_item.qos_info.drb_qos.alloc_and_retention_prio.pre_emption_vulnerability = "not_pre_emptable";
    drb_item.qos_info.s_nssai.sst                                                = 1;
    drb_item.rlc_mod                                                             = rlc_mode::am;
    drb_item.pdcp_sn_len                                                         = pdcp_sn_size::size12bits;

    req.drbs_to_be_setup_list.emplace(drb, drb_item);
  }
  return req;
}
