/*
 *
 * Copyright 2013-2022 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "../../lib/rlc/rlc_am_entity.h"
#include <gtest/gtest.h>
#include <queue>

using namespace srsgnb;

template <std::size_t N>
byte_buffer make_byte_buffer_and_log(const std::array<uint8_t, N>& tv)
{
  byte_buffer sdu = {tv};
  return sdu;
}

template <std::size_t N>
byte_buffer_slice_chain make_rlc_byte_buffer_and_log(const std::array<uint8_t, N>& tv)
{
  byte_buffer             buf = {tv};
  byte_buffer_slice_chain pdu;
  pdu.push_back(std::move(buf));
  return pdu;
}

/// Mocking class of the surrounding layers invoked by the RLC.
class rlc_test_frame : public rlc_rx_upper_layer_data_notifier,
                       public rlc_tx_upper_layer_data_notifier,
                       public rlc_tx_upper_layer_control_notifier,
                       public rlc_tx_buffer_state_update_notifier
{
public:
  std::queue<byte_buffer_slice> sdu_queue;
  uint32_t                      sdu_counter = 0;

  // rlc_rx_upper_layer_data_notifier interface
  void on_new_sdu(byte_buffer_slice sdu) override
  {
    sdu_queue.push(std::move(sdu));
    sdu_counter++;
  }

  // rlc_tx_upper_layer_data_notifier interface
  void on_delivered_sdu(uint32_t pdcp_count) override {}

  // rlc_tx_upper_layer_control_notifier interface
  void on_protocol_failure() override {}
  void on_max_retx() override{};

  // rlc_tx_buffer_state_update_notifier interface
  void on_buffer_state_update(unsigned bsr) override {}
};

/// Fixture class for RLC AM Tx tests
/// It requires TEST_P() and INSTANTIATE_TEST_SUITE_P() to create/spawn tests for each supported SN size
class rlc_tx_am_test : public ::testing::Test, public ::testing::WithParamInterface<rlc_am_sn_size>
{
protected:
  void SetUp() override
  {
    // init test's logger
    srslog::init();
    logger.set_level(srslog::basic_levels::debug);

    // init RLC logger
    srslog::fetch_basic_logger("RLC", false).set_level(srslog::basic_levels::debug);
    srslog::fetch_basic_logger("RLC", false).set_hex_dump_max_size(100);
  }

  void TearDown() override
  {
    // flush logger after each test
    srslog::flush();
  }

  /// \brief Initializes fixture according to size sequence number size
  /// \param sn_size_ size of the sequence number
  void init(rlc_am_sn_size sn_size_)
  {
    logger.info("Creating RLC AM ({} bit)", to_number(sn_size));

    sn_size = sn_size_;

    // Set Rx config
    config.rx                    = std::make_unique<rlc_rx_am_config>(rlc_rx_am_config{});
    config.rx->sn_field_length   = sn_size;
    config.rx->t_reassembly      = 35;
    config.rx->t_status_prohibit = 8;

    // Set Tx config
    config.tx                  = std::make_unique<rlc_tx_am_config>(rlc_tx_am_config{});
    config.tx->sn_field_length = sn_size;
    config.tx->t_poll_retx     = 45;
    config.tx->max_retx_thresh = 4;
    config.tx->poll_pdu        = 4;
    config.tx->poll_byte       = 25;

    // Create RLC entities
    rlc1 = std::make_unique<rlc_am_entity>(
        du_ue_index_t::MIN_DU_UE_INDEX, lcid_t::LCID_SRB0, config, tester1, tester1, tester1, tester1, timers);
    rlc2 = std::make_unique<rlc_am_entity>(
        du_ue_index_t::MIN_DU_UE_INDEX, lcid_t::LCID_SRB0, config, tester2, tester2, tester2, tester2, timers);

    // Bind interfaces
    rlc1_rx_lower = rlc1->get_rx_pdu_handler();
    rlc1_tx_upper = rlc1->get_tx_sdu_handler();
    rlc1_tx_lower = rlc1->get_tx_pdu_transmitter();
    rlc2_rx_lower = rlc2->get_rx_pdu_handler();
    rlc2_tx_upper = rlc2->get_tx_sdu_handler();
    rlc2_tx_lower = rlc2->get_tx_pdu_transmitter();
  }

  /// \brief Creates a byte_buffer serving as SDU for RLC
  ///
  /// The produced SDU contains an incremental sequence of bytes starting with the value given by first_byte,
  /// i.e. if first_byte = 0xfc, the SDU will be 0xfc 0xfe 0xff 0x00 0x01 ...
  /// \param sdu_size Size of the SDU
  /// \param first_byte Value of the first byte
  /// \return the produced SDU as a byte_buffer
  byte_buffer create_sdu(uint32_t sdu_size, uint8_t first_byte = 0) const
  {
    byte_buffer sdu_buf;
    for (uint32_t k = 0; k < sdu_size; ++k) {
      sdu_buf.append(first_byte + k);
    }
    return sdu_buf;
  }

  /// \brief Creates a new rlc_sdu
  ///
  /// The produced SDU contains an incremental sequence of bytes starting with the value given by first_byte,
  /// i.e. if first_byte = 0xfc, the SDU will be 0xfc 0xfe 0xff 0x00 0x01 ...
  /// \param pdcp_count PDCP count value
  /// \param sdu_size Size of the SDU
  /// \param first_byte Value of the first byte
  /// \return the produced SDU as a rlc_sdu
  rlc_sdu create_rlc_sdu(uint32_t pdcp_count, uint32_t sdu_size, uint8_t first_byte = 0) const
  {
    rlc_sdu sdu = {pdcp_count, create_sdu(sdu_size, first_byte)};
    return sdu;
  }

  /// \brief Obtains full RLC AMD PDUs from generated SDUs that are passed through an RLC AM entity
  /// \param[out] out_pdus Pre-allocated array of size n_pdus for the resulting RLC AMD PDUs
  /// \param[in] n_pdus Length of the out_pdus array
  /// \param[in] sdu_size Size of SDU that is passed through RLC AM entity
  void tx_full_pdus(byte_buffer_slice_chain* out_pdus, uint32_t n_pdus, uint32_t sdu_size = 1)
  {
    // Push "n_pdus" SDUs into RLC1
    byte_buffer sdu_bufs[n_pdus];
    for (uint32_t i = 0; i < n_pdus; i++) {
      sdu_bufs[i] = create_sdu(sdu_size, i);

      // write SDU into upper end
      rlc_sdu sdu = {i, sdu_bufs[i].deep_copy()}; // no std::move - keep local copy for later comparison
      rlc1_tx_upper->handle_sdu(std::move(sdu));
    }

    uint32_t header_size         = sn_size == rlc_am_sn_size::size12bits ? 2 : 3;
    uint32_t data_pdu_size       = header_size + sdu_size;
    uint32_t expect_buffer_state = n_pdus * data_pdu_size;

    // Read "n_pdus" PDUs from RLC1
    for (uint32_t i = 0; i < n_pdus; i++) {
      EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), expect_buffer_state - i * data_pdu_size);
      out_pdus[i] = rlc1_tx_lower->pull_pdu(data_pdu_size);
      EXPECT_EQ(out_pdus[i].length(), data_pdu_size);
      EXPECT_TRUE(
          std::equal(out_pdus[i].begin() + header_size, out_pdus[i].end(), sdu_bufs[i].begin(), sdu_bufs[i].end()));
    }
    EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);
  }

  /// \brief Obtains RLC AMD PDU segments from generated SDUs that are passed through an RLC AM entity
  /// \param[out] out_pdus Pre-allocated array of size n_pdus for the resulting RLC AMD PDU segments
  /// \param[in] n_pdus Length of the out_pdus array
  /// \param[in] pdu_size Maximum size of each PDU that is read from RLC AM entity
  /// \param[in] n_sdus Number of SDUs to push into RLC AM entity
  /// \param[in] sdu_size Size of each SDU that is pushed into RLC AM entity
  void tx_segmented_pdus(byte_buffer_slice_chain* out_pdus,
                         uint32_t                 n_pdus,
                         uint32_t                 pdu_size,
                         uint32_t                 n_sdus,
                         uint32_t                 sdu_size)
  {
    uint32_t header_min_size = sn_size == rlc_am_sn_size::size12bits ? 2 : 3;
    uint32_t header_so_size  = 2;

    // Precondition
    ASSERT_LT(pdu_size, sdu_size + header_min_size) << "PDU size fits whole SDU; PDUs won't be segmented";

    // Push "n_sdus" SDUs into RLC1
    byte_buffer sdu_bufs[n_sdus];
    for (uint32_t i = 0; i < n_sdus; i++) {
      sdu_bufs[i] = create_sdu(sdu_size, i);

      // write SDU into upper end
      rlc_sdu sdu = {i, sdu_bufs[i].deep_copy()}; // no std::move - keep local copy for later comparison
      rlc1_tx_upper->handle_sdu(std::move(sdu));
    }

    // Read "n_pdus" PDUs from RLC1
    uint32_t sdu_idx = 0;
    uint32_t sdu_so  = 0;
    for (uint32_t i = 0; i < n_pdus && rlc1_tx_lower->get_buffer_state() > 0; i++) {
      uint32_t header_size = header_min_size + (sdu_so == 0 ? 0 : header_so_size);
      out_pdus[i]          = rlc1_tx_lower->pull_pdu(pdu_size);

      // Check PDU size
      EXPECT_GT(out_pdus[i].length(), header_size);
      EXPECT_LE(out_pdus[i].length(), pdu_size);

      // Check PDU payload
      auto pdu_begin = out_pdus[i].begin() + header_size;
      auto pdu_end   = out_pdus[i].end();
      auto sdu_begin = sdu_bufs[sdu_idx].begin() + sdu_so;
      ASSERT_TRUE(std::equal(pdu_begin, pdu_end, sdu_begin))
          << "sdu_idx=" << sdu_idx << ", sdu_so=" << sdu_so << ", i=" << i << ", header_size=" << header_size;

      // Check remaining buffer state
      uint32_t rem_sdus      = n_sdus - sdu_idx - 1;
      uint32_t rem_seg_bytes = sdu_bufs[sdu_idx].length() - sdu_so - out_pdus[i].length() + header_size;
      uint32_t rem_seg_hdr   = rem_seg_bytes > 0 ? header_min_size + header_so_size : 0;
      EXPECT_EQ(rlc1_tx_lower->get_buffer_state(),
                rem_sdus * (sdu_size + header_min_size) + rem_seg_bytes + rem_seg_hdr);

      // Update payload offsets
      if (rem_seg_bytes == 0) {
        sdu_idx++;
        sdu_so = 0;
      } else {
        sdu_so += out_pdus[i].length() - header_size;
      }
    }
    EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);
  }

  srslog::basic_logger&          logger  = srslog::fetch_basic_logger("TEST", false);
  rlc_am_sn_size                 sn_size = GetParam();
  rlc_am_config                  config;
  timer_manager                  timers;
  rlc_test_frame                 tester1, tester2;
  std::unique_ptr<rlc_am_entity> rlc1, rlc2;
  rlc_rx_pdu_handler*            rlc1_rx_lower = nullptr;
  rlc_tx_sdu_handler*            rlc1_tx_upper = nullptr;
  rlc_tx_pdu_transmitter*        rlc1_tx_lower = nullptr;
  rlc_rx_pdu_handler*            rlc2_rx_lower = nullptr;
  rlc_tx_sdu_handler*            rlc2_tx_upper = nullptr;
  rlc_tx_pdu_transmitter*        rlc2_tx_lower = nullptr;
};

TEST_P(rlc_tx_am_test, create_new_entity)
{
  init(GetParam());
  EXPECT_NE(rlc1_rx_lower, nullptr);
  EXPECT_NE(rlc1_tx_upper, nullptr);
  ASSERT_NE(rlc1_tx_lower, nullptr);
  EXPECT_NE(rlc2_rx_lower, nullptr);
  EXPECT_NE(rlc2_tx_upper, nullptr);
  ASSERT_NE(rlc2_tx_lower, nullptr);

  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);
  EXPECT_EQ(rlc2_tx_lower->get_buffer_state(), 0);
}

TEST_P(rlc_tx_am_test, tx_without_segmentation)
{
  init(GetParam());
  const uint32_t          n_pdus = 5;
  byte_buffer_slice_chain pdus[n_pdus];

  tx_full_pdus(pdus, n_pdus, 1);
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);

  tx_full_pdus(pdus, n_pdus, 5);
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);
}

TEST_P(rlc_tx_am_test, tx_small_grant_)
{
  init(GetParam());
  const uint32_t n_sdus   = 5;
  const uint32_t sdu_size = 9;

  const uint32_t n_splits = 3;

  const uint32_t n_pdus      = n_sdus * n_splits;
  const uint32_t header_size = (sn_size == rlc_am_sn_size::size12bits ? 2 : 3);
  const uint32_t so_size     = 2;
  const uint32_t pdu_size    = header_size + so_size + (sdu_size / n_splits);

  byte_buffer_slice_chain pdus[n_pdus];

  tx_segmented_pdus(pdus, n_pdus, pdu_size, n_sdus, sdu_size);
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);

  tx_segmented_pdus(pdus, n_pdus, pdu_size, n_sdus, sdu_size);
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);
}

TEST_P(rlc_tx_am_test, tx_insufficient_space_new_sdu)
{
  init(GetParam());
  const uint32_t sdu_size        = 1;
  const uint32_t header_min_size = sn_size == rlc_am_sn_size::size12bits ? 2 : 3;
  const uint32_t short_size      = header_min_size;
  const uint32_t fit_size        = header_min_size + sdu_size;

  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);
  rlc1_tx_upper->handle_sdu(create_rlc_sdu(0, sdu_size));
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), sdu_size + header_min_size);

  byte_buffer_slice_chain pdu;

  // short read - expect empty PDU
  pdu = rlc1_tx_lower->pull_pdu(short_size);
  EXPECT_EQ(pdu.length(), 0);
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), sdu_size + header_min_size);

  // fitting read
  pdu = rlc1_tx_lower->pull_pdu(fit_size);
  EXPECT_EQ(pdu.length(), fit_size);
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);
}

TEST_P(rlc_tx_am_test, tx_insufficient_space_continued_sdu)
{
  init(GetParam());
  const uint32_t sdu_size        = 3;
  const uint32_t header_min_size = sn_size == rlc_am_sn_size::size12bits ? 2 : 3;
  const uint32_t header_so_size  = 2;
  const uint32_t min_size_first  = header_min_size + 1;
  const uint32_t short_size      = header_min_size + header_so_size;
  const uint32_t min_size_seg    = header_min_size + header_so_size + 1;

  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);
  rlc1_tx_upper->handle_sdu(create_rlc_sdu(0, sdu_size));
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), sdu_size + header_min_size);

  byte_buffer_slice_chain pdu;

  // kick-off segmentation
  pdu = rlc1_tx_lower->pull_pdu(min_size_first);
  EXPECT_EQ(pdu.length(), min_size_first);
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), (sdu_size - 1) + header_min_size + header_so_size);

  // short read - expect empty PDU
  pdu = rlc1_tx_lower->pull_pdu(short_size);
  EXPECT_EQ(pdu.length(), 0);
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), (sdu_size - 1) + header_min_size + header_so_size);

  // minimum-length read (middle segment)
  pdu = rlc1_tx_lower->pull_pdu(min_size_seg);
  EXPECT_EQ(pdu.length(), min_size_seg);
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), (sdu_size - 2) + header_min_size + header_so_size);

  // minimum-length read (last segment)
  pdu = rlc1_tx_lower->pull_pdu(min_size_seg);
  EXPECT_EQ(pdu.length(), min_size_seg);
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);
}

TEST_P(rlc_tx_am_test, retx_pdu_without_segmentation)
{
  init(GetParam());
  const uint32_t          sdu_size        = 3;
  const uint32_t          header_min_size = sn_size == rlc_am_sn_size::size12bits ? 2 : 3;
  const uint32_t          n_pdus          = 5;
  byte_buffer_slice_chain pdus[n_pdus];

  tx_full_pdus(pdus, n_pdus, sdu_size);
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);

  // NACK SN=3
  rlc_am_status_nack nack = {};
  nack.nack_sn            = 3;
  rlc_am_status_pdu status_pdu(sn_size);
  status_pdu.ack_sn = n_pdus;
  status_pdu.push_nack(nack);
  byte_buffer status_pdu_buf;
  status_pdu.pack(status_pdu_buf);
  rlc1_rx_lower->handle_pdu(std::move(status_pdu_buf));
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), sdu_size + header_min_size);

  // Read ReTx as full PDU
  byte_buffer_slice_chain retx_pdu;
  retx_pdu = rlc1_tx_lower->pull_pdu(sdu_size + header_min_size);
  logger.debug(retx_pdu.begin(), retx_pdu.end(), "retx_pdu:");
  logger.debug(pdus[nack.nack_sn].begin(), pdus[nack.nack_sn].end(), "pdus[{}]:", nack.nack_sn);
  EXPECT_TRUE(std::equal(retx_pdu.begin(), retx_pdu.end(), pdus[nack.nack_sn].begin(), pdus[nack.nack_sn].end()));
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);
}

TEST_P(rlc_tx_am_test, retx_pdu_with_segmentation)
{
  init(GetParam());
  const uint32_t          sdu_size        = 3;
  const uint32_t          header_min_size = sn_size == rlc_am_sn_size::size12bits ? 2 : 3;
  const uint32_t          so_size         = 2;
  const uint32_t          header_max_size = header_min_size + so_size;
  const uint32_t          n_pdus          = 5;
  byte_buffer_slice_chain pdus[n_pdus];

  tx_full_pdus(pdus, n_pdus, sdu_size);
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);

  // NACK SN=3
  rlc_am_status_nack nack = {};
  nack.nack_sn            = 3;
  rlc_am_status_pdu status_pdu(sn_size);
  status_pdu.ack_sn = n_pdus;
  status_pdu.push_nack(nack);
  byte_buffer status_pdu_buf;
  status_pdu.pack(status_pdu_buf);
  rlc1_rx_lower->handle_pdu(std::move(status_pdu_buf));
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), sdu_size + header_min_size);

  // Read ReTx in segments
  byte_buffer_slice_chain retx_pdu;
  for (uint32_t i = 0; i < sdu_size; i++) {
    uint32_t header_size = i == 0 ? header_min_size : header_max_size;
    retx_pdu             = rlc1_tx_lower->pull_pdu(1 + header_size);
    logger.debug(retx_pdu.begin(), retx_pdu.end(), "retx_pdu:");
    logger.debug(pdus[nack.nack_sn].begin(), pdus[nack.nack_sn].end(), "pdus[{}]:", nack.nack_sn);
    EXPECT_TRUE(
        std::equal(retx_pdu.begin() + header_size, retx_pdu.end(), pdus[nack.nack_sn].begin() + header_min_size + i));
  }
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);
}

TEST_P(rlc_tx_am_test, retx_pdu_first_segment_without_segmentation)
{
  init(GetParam());
  const uint32_t          sdu_size        = 3;
  const uint32_t          header_min_size = sn_size == rlc_am_sn_size::size12bits ? 2 : 3;
  const uint32_t          n_pdus          = 5;
  byte_buffer_slice_chain pdus[n_pdus];

  tx_full_pdus(pdus, n_pdus, sdu_size);
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);

  // NACK SN=3 0:1
  rlc_am_status_nack nack = {};
  nack.nack_sn            = 3;
  nack.so_start           = 0;
  nack.so_end             = 1;
  nack.has_so             = true;
  rlc_am_status_pdu status_pdu(sn_size);
  status_pdu.ack_sn = n_pdus;
  status_pdu.push_nack(nack);
  byte_buffer status_pdu_buf;
  status_pdu.pack(status_pdu_buf);
  rlc1_rx_lower->handle_pdu(std::move(status_pdu_buf));
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), nack.so_end - nack.so_start + 1 + header_min_size);

  // Read ReTx without extra segmentation
  byte_buffer_slice_chain retx_pdu;
  retx_pdu = rlc1_tx_lower->pull_pdu(sdu_size + header_min_size);
  logger.debug(retx_pdu.begin(), retx_pdu.end(), "retx_pdu:");
  logger.debug(pdus[nack.nack_sn].begin(), pdus[nack.nack_sn].end(), "pdus[{}]:", nack.nack_sn);
  EXPECT_TRUE(
      std::equal(retx_pdu.begin() + header_min_size, retx_pdu.end(), pdus[nack.nack_sn].begin() + header_min_size));
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);
}

TEST_P(rlc_tx_am_test, retx_pdu_middle_segment_without_segmentation)
{
  init(GetParam());
  const uint32_t          sdu_size        = 3;
  const uint32_t          header_min_size = sn_size == rlc_am_sn_size::size12bits ? 2 : 3;
  const uint32_t          so_size         = 2;
  const uint32_t          header_max_size = header_min_size + so_size;
  const uint32_t          n_pdus          = 5;
  byte_buffer_slice_chain pdus[n_pdus];

  tx_full_pdus(pdus, n_pdus, sdu_size);
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);

  // NACK SN=3 1:1
  rlc_am_status_nack nack = {};
  nack.nack_sn            = 3;
  nack.so_start           = 1;
  nack.so_end             = 1;
  nack.has_so             = true;
  rlc_am_status_pdu status_pdu(sn_size);
  status_pdu.ack_sn = n_pdus;
  status_pdu.push_nack(nack);
  byte_buffer status_pdu_buf;
  status_pdu.pack(status_pdu_buf);
  rlc1_rx_lower->handle_pdu(std::move(status_pdu_buf));
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), nack.so_end - nack.so_start + 1 + header_max_size);

  // Read ReTx without extra segmentation
  byte_buffer_slice_chain retx_pdu;
  retx_pdu = rlc1_tx_lower->pull_pdu(sdu_size + header_max_size);
  logger.debug(retx_pdu.begin(), retx_pdu.end(), "retx_pdu:");
  logger.debug(pdus[nack.nack_sn].begin(), pdus[nack.nack_sn].end(), "pdus[{}]:", nack.nack_sn);
  EXPECT_TRUE(std::equal(retx_pdu.begin() + header_max_size,
                         retx_pdu.end(),
                         pdus[nack.nack_sn].begin() + header_min_size + nack.so_start));
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);
}

TEST_P(rlc_tx_am_test, retx_pdu_last_segment_without_segmentation)
{
  init(GetParam());
  const uint32_t          sdu_size        = 3;
  const uint32_t          header_min_size = sn_size == rlc_am_sn_size::size12bits ? 2 : 3;
  const uint32_t          so_size         = 2;
  const uint32_t          header_max_size = header_min_size + so_size;
  const uint32_t          n_pdus          = 5;
  byte_buffer_slice_chain pdus[n_pdus];

  tx_full_pdus(pdus, n_pdus, sdu_size);
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);

  // NACK SN=3 1:2
  rlc_am_status_nack nack = {};
  nack.nack_sn            = 3;
  nack.so_start           = 1;
  nack.so_end             = 2;
  nack.has_so             = true;
  rlc_am_status_pdu status_pdu(sn_size);
  status_pdu.ack_sn = n_pdus;
  status_pdu.push_nack(nack);
  byte_buffer status_pdu_buf;
  status_pdu.pack(status_pdu_buf);
  rlc1_rx_lower->handle_pdu(std::move(status_pdu_buf));
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), nack.so_end - nack.so_start + 1 + header_max_size);

  // Read ReTx without extra segmentation
  byte_buffer_slice_chain retx_pdu;
  retx_pdu = rlc1_tx_lower->pull_pdu(sdu_size + header_max_size);
  logger.debug(retx_pdu.begin(), retx_pdu.end(), "retx_pdu:");
  logger.debug(pdus[nack.nack_sn].begin(), pdus[nack.nack_sn].end(), "pdus[{}]:", nack.nack_sn);
  EXPECT_TRUE(std::equal(retx_pdu.begin() + header_max_size,
                         retx_pdu.end(),
                         pdus[nack.nack_sn].begin() + header_min_size + nack.so_start));
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);
}

TEST_P(rlc_tx_am_test, retx_pdu_segment_invalid_so_start_and_so_end)
{
  init(GetParam());
  const uint32_t          sdu_size        = 3;
  const uint32_t          header_min_size = sn_size == rlc_am_sn_size::size12bits ? 2 : 3;
  const uint32_t          n_pdus          = 5;
  byte_buffer_slice_chain pdus[n_pdus];

  tx_full_pdus(pdus, n_pdus, sdu_size);
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);

  // NACK SN=3 3:3
  rlc_am_status_nack nack = {};
  nack.nack_sn            = 3;
  nack.so_start           = 3; // out of bounds
  nack.so_end             = 3; // out of bounds
  nack.has_so             = true;
  rlc_am_status_pdu status_pdu(sn_size);
  status_pdu.ack_sn = n_pdus;
  status_pdu.push_nack(nack);
  byte_buffer status_pdu_buf;
  status_pdu.pack(status_pdu_buf);
  rlc1_rx_lower->handle_pdu(std::move(status_pdu_buf));
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), sdu_size + header_min_size);

  // Read ReTx without extra segmentation
  byte_buffer_slice_chain retx_pdu;
  retx_pdu = rlc1_tx_lower->pull_pdu(sdu_size + header_min_size);
  logger.debug(retx_pdu.begin(), retx_pdu.end(), "retx_pdu:");
  logger.debug(pdus[nack.nack_sn].begin(), pdus[nack.nack_sn].end(), "pdus[{}]:", nack.nack_sn);
  EXPECT_TRUE(
      std::equal(retx_pdu.begin() + header_min_size, retx_pdu.end(), pdus[nack.nack_sn].begin() + header_min_size));
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);
}

TEST_P(rlc_tx_am_test, retx_pdu_segment_invalid_so_start_larger_than_so_end)
{
  init(GetParam());
  const uint32_t          sdu_size        = 3;
  const uint32_t          header_min_size = sn_size == rlc_am_sn_size::size12bits ? 2 : 3;
  const uint32_t          n_pdus          = 5;
  byte_buffer_slice_chain pdus[n_pdus];

  tx_full_pdus(pdus, n_pdus, sdu_size);
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);

  // NACK SN=3 3:2
  rlc_am_status_nack nack = {};
  nack.nack_sn            = 3;
  nack.so_start           = 2; // larger than so_end
  nack.so_end             = 1; // smaller than so_start
  nack.has_so             = true;
  rlc_am_status_pdu status_pdu(sn_size);
  status_pdu.ack_sn = n_pdus;
  status_pdu.push_nack(nack);
  byte_buffer status_pdu_buf;
  status_pdu.pack(status_pdu_buf);
  rlc1_rx_lower->handle_pdu(std::move(status_pdu_buf));
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), nack.so_end + 1 + header_min_size);

  // Read ReTx without extra segmentation
  byte_buffer_slice_chain retx_pdu;
  retx_pdu = rlc1_tx_lower->pull_pdu(sdu_size + header_min_size);
  logger.debug(retx_pdu.begin(), retx_pdu.end(), "retx_pdu:");
  logger.debug(pdus[nack.nack_sn].begin(), pdus[nack.nack_sn].end(), "pdus[{}]:", nack.nack_sn);
  EXPECT_TRUE(
      std::equal(retx_pdu.begin() + header_min_size, retx_pdu.end(), pdus[nack.nack_sn].begin() + header_min_size));
  EXPECT_EQ(rlc1_tx_lower->get_buffer_state(), 0);
}

///////////////////////////////////////////////////////////////////////////////
// Finally, instantiate all testcases for each supported SN size
///////////////////////////////////////////////////////////////////////////////

std::string test_param_info_to_string(const ::testing::TestParamInfo<rlc_am_sn_size>& info)
{
  fmt::memory_buffer buffer;
  fmt::format_to(buffer, "{}bit", to_number(info.param));
  return fmt::to_string(buffer);
}

INSTANTIATE_TEST_SUITE_P(rlc_tx_am_test_each_sn_size,
                         rlc_tx_am_test,
                         ::testing::Values(rlc_am_sn_size::size12bits, rlc_am_sn_size::size18bits),
                         test_param_info_to_string);