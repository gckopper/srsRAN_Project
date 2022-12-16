/*
 *
 * Copyright 2013-2022 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "upper_phy_rx_symbol_handler_impl.h"
#include "upper_phy_rx_results_notifier_wrapper.h"
#include "srsgnb/phy/support/prach_buffer_context.h"
#include "srsgnb/phy/support/resource_grid.h"
#include "srsgnb/phy/upper/uplink_processor.h"
#include "srsgnb/support/error_handling.h"

using namespace srsgnb;

upper_phy_rx_symbol_handler_impl::upper_phy_rx_symbol_handler_impl(uplink_processor_pool&         ul_processor_pool_,
                                                                   uplink_slot_pdu_repository&    ul_pdu_repository_,
                                                                   rx_softbuffer_pool&            softbuffer_pool_,
                                                                   upper_phy_rx_results_notifier& rx_results_notifier_,
                                                                   srslog::basic_logger&          logger_) :
  ul_processor_pool(ul_processor_pool_),
  ul_pdu_repository(ul_pdu_repository_),
  softbuffer_pool(softbuffer_pool_),
  rx_results_notifier(rx_results_notifier_),
  logger(logger_)
{
}

/// Returns the cyclic prefix from the given uplink processor PUCCH PDU.
static cyclic_prefix get_cp(const uplink_processor::pucch_pdu& pdu)
{
  switch (pdu.context.format) {
    case pucch_format::FORMAT_0:
      return pdu.format0.cp;
    case pucch_format::FORMAT_1:
      return pdu.format1.cp;
    case pucch_format::FORMAT_2:
      return pdu.format2.cp;
    case pucch_format::FORMAT_3:
      return pdu.format3.cp;
    case pucch_format::FORMAT_4:
      return pdu.format4.cp;
    default:
      srsgnb_assert(0, "Invalid PUCCH format={}", pdu.context.format);
      break;
  }

  return cyclic_prefix::NORMAL;
}

void upper_phy_rx_symbol_handler_impl::handle_rx_symbol(const upper_phy_rx_symbol_context& context,
                                                        const resource_grid_reader&        grid)
{
  // Check if all the symbols are present in the grid.
  span<const uplink_slot_pdu_entry> pdus = ul_pdu_repository.get_pdus(context.slot);

  srsgnb_assert(!pdus.empty(),
                "Received notification for processing an uplink slot, but no PUSCH/PUCCH PDUs are expected to be "
                "processed in the slot={}",
                context.slot);

  const uplink_slot_pdu_entry& first_entry = pdus.front();
  unsigned                     nof_symbols =
      get_nsymb_per_slot((first_entry.type == uplink_slot_pdu_entry::pdu_type::PUSCH) ? first_entry.pusch.pdu.cp
                                                                                      : get_cp(first_entry.pucch));
  unsigned last_symbol_id = nof_symbols - 1U;

  // Process the PDUs when all symbols of the slot have been received.
  if (context.symbol != last_symbol_id) {
    return;
  }

  // Get the uplink processor.
  uplink_processor& ul_processor = ul_processor_pool.get_processor(context.slot, context.sector);

  // Process all the PDUs from the pool.
  for (const auto& pdu : pdus) {
    switch (pdu.type) {
      case uplink_slot_pdu_entry::pdu_type::PUSCH:
        process_pusch(pdu.pusch, ul_processor, grid, context.slot);
        break;
      case uplink_slot_pdu_entry::pdu_type::PUCCH:
        ul_processor.process_pucch(rx_results_notifier, grid, pdu.pucch);
        break;
    }
  }
}

void upper_phy_rx_symbol_handler_impl::handle_rx_prach_window(const prach_buffer_context& context,
                                                              const prach_buffer&         buffer)
{
  // Get uplink processor.
  uplink_processor& ul_processor = ul_processor_pool.get_processor(context.slot, context.sector);

  // Process PRACH.
  ul_processor.process_prach(rx_results_notifier, buffer, context);
}

void upper_phy_rx_symbol_handler_impl::handle_rx_srs_symbol(const upper_phy_rx_symbol_context& context)
{
  report_fatal_error("upper_phy_rx_symbol_handler_impl::handle_rx_srs_symbol not yet implemented");
}

void upper_phy_rx_symbol_handler_impl::process_pusch(const uplink_processor::pusch_pdu& pdu,
                                                     uplink_processor&                  ul_processor,
                                                     const resource_grid_reader&        grid,
                                                     slot_point                         slot)
{
  const pusch_processor::pdu_t& proc_pdu = pdu.pdu;

  // Temporal sanity check as PUSCH is only supported for data. Remove the check when the UCI is supported for PUSCH.
  srsgnb_assert(proc_pdu.codeword.has_value(), "PUSCH PDU doesn't contain data. Currently, that mode is not supported");

  rx_softbuffer_identifier id;
  id.rnti        = static_cast<unsigned>(proc_pdu.rnti);
  id.harq_ack_id = pdu.harq_id;

  const unsigned BITS_PER_BYTE = 8;
  unsigned       nof_codeblocks =
      ldpc::compute_nof_codeblocks(pdu.tb_size * BITS_PER_BYTE, proc_pdu.codeword->ldpc_base_graph);

  if (rx_softbuffer* buffer = softbuffer_pool.reserve_softbuffer(slot, id, nof_codeblocks)) {
    auto payload = rx_payload_pool.acquire_payload_buffer(pdu.tb_size);
    ul_processor.process_pusch(payload, *buffer, rx_results_notifier, grid, pdu);
    return;
  }

  logger.warning("Could not reserve a softbuffer for PUSCH PDU with RNTI={}, HARQ={} and slot={}",
                 id.rnti,
                 id.harq_ack_id,
                 proc_pdu.slot);
}
