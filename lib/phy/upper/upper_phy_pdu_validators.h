/*
 *
 * Copyright 2013-2022 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "srsgnb/phy/upper/downlink_processor.h"
#include "srsgnb/phy/upper/uplink_processor.h"

namespace srsgnb {

/// Implements the uplink PDU validator for \ref uplink_processor_single_executor_impl.
class uplink_processor_validator_impl : public uplink_pdu_validator
{
public:
  /// Constructs an uplink PDU validator containing the validators for each channel.
  uplink_processor_validator_impl(std::unique_ptr<prach_detector_validator> prach_,
                                  std::unique_ptr<pucch_pdu_validator>      pucch_,
                                  std::unique_ptr<pusch_pdu_validator>      pusch_) :
    prach(std::move(prach_)), pucch(std::move(pucch_)), pusch(std::move(pusch_))
  {
    srsgnb_assert(prach, "Invalid PRACH detector validator.");
    srsgnb_assert(pucch, "Invalid PUCCH processor validator.");
    srsgnb_assert(pusch, "Invalid PUSCH processor validator.");
  }

  // See interface for documentation.
  bool is_valid(const prach_detector::configuration& config) const override { return prach->is_valid(config); }
  bool is_valid(const pucch_processor::format0_configuration& config) const override { return pucch->is_valid(config); }
  bool is_valid(const pucch_processor::format1_configuration& config) const override { return pucch->is_valid(config); }
  bool is_valid(const pucch_processor::format2_configuration& config) const override { return pucch->is_valid(config); }
  bool is_valid(const pucch_processor::format3_configuration& config) const override { return pucch->is_valid(config); }
  bool is_valid(const pucch_processor::format4_configuration& config) const override { return pucch->is_valid(config); }
  bool is_valid(const pusch_processor::pdu_t& pdu) const override { return pusch->is_valid(pdu); }

private:
  std::unique_ptr<prach_detector_validator> prach;
  std::unique_ptr<pucch_pdu_validator>      pucch;
  std::unique_ptr<pusch_pdu_validator>      pusch;
};

/// Implements the downlink PDU validator for \ref downlink_processor_single_executor_impl.
class downlink_processor_validator_impl : public downlink_pdu_validator
{
public:
  /// Constructs an downlink PDU validator containing the validators for each channel.
  downlink_processor_validator_impl(std::unique_ptr<ssb_pdu_validator>   ssb_,
                                    std::unique_ptr<pdcch_pdu_validator> pdcch_,
                                    std::unique_ptr<pdsch_pdu_validator> pdsch_) :
    ssb(std::move(ssb_)), pdcch(std::move(pdcch_)), pdsch(std::move(pdsch_))
  {
    srsgnb_assert(ssb, "Invalid SSB processor validator.");
    srsgnb_assert(pdcch, "Invalid PDCCH processor validator.");
    srsgnb_assert(pdsch, "Invalid PDSCH processor validator.");
  }

  // See interface for documentation.
  bool is_valid(const ssb_processor::pdu_t& pdu) const override { return ssb->is_valid(pdu); }
  bool is_valid(const pdcch_processor::pdu_t& pdu) const override { return pdcch->is_valid(pdu); }
  bool is_valid(const pdsch_processor::pdu_t& pdu) const override { return pdsch->is_valid(pdu); }

private:
  std::unique_ptr<ssb_pdu_validator>   ssb;
  std::unique_ptr<pdcch_pdu_validator> pdcch;
  std::unique_ptr<pdsch_pdu_validator> pdsch;
};

} // namespace srsgnb
