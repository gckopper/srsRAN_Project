/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "ue_manager_test_helpers.h"
#include <gtest/gtest.h>

using namespace srsran;
using namespace srs_cu_cp;

//////////////////////////////////////////////////////////////////////////////////////
/* DU UE                                                                            */
//////////////////////////////////////////////////////////////////////////////////////

/// Test allocation of multiple UE indexes
TEST_F(ue_manager_test, when_multiple_ue_indexes_allocated_then_ue_indexes_valid)
{
  du_index_t du_index = du_index_t::min;

  // reduce log level to avoid flooding the log
  ue_mng_logger.set_level(srslog::basic_levels::warning);
  test_logger.set_level(srslog::basic_levels::warning);

  for (unsigned it = 0; it < ue_mng.get_ue_config().max_nof_supported_ues; it++) {
    // Check that the ue index is valid
    ASSERT_NE(ue_mng.add_ue(du_index), ue_index_t::invalid);
  }
}

/// Test allocation of unsupported number of UE indexes
TEST_F(ue_manager_test, when_more_than_max_ue_indexes_allocated_then_ue_index_invalid)
{
  du_index_t du_index = du_index_t::min;

  // reduce log level to avoid flooding the log
  ue_mng_logger.set_level(srslog::basic_levels::warning);
  test_logger.set_level(srslog::basic_levels::warning);

  for (unsigned it = 0; it < ue_mng.get_ue_config().max_nof_supported_ues; it++) {
    // Check that the ue index is valid
    ASSERT_NE(ue_mng.add_ue(du_index), ue_index_t::invalid);
  }

  // reset log level
  ue_mng_logger.set_level(srslog::basic_levels::debug);
  test_logger.set_level(srslog::basic_levels::debug);

  // Allocate additional ue index
  ASSERT_EQ(ue_mng.add_ue(du_index), ue_index_t::invalid);
}

/// Test successful creation of a DU UE
TEST_F(ue_manager_test, when_valid_du_context_added_at_creation_then_ue_added)
{
  du_index_t      du_index    = du_index_t::min;
  rnti_t          rnti        = to_rnti(0x4601);
  du_cell_index_t pcell_index = du_cell_index_t::min;
  ue_index_t      ue_index    = ue_mng.add_ue(du_index, gnb_du_id_t::min, MIN_PCI, rnti, pcell_index);
  auto*           ue          = ue_mng.find_ue(ue_index);

  // check that the UE has been created
  ASSERT_NE(ue, nullptr);
  ASSERT_NE(ue_mng.find_du_ue(ue->get_ue_index()), nullptr);

  // check that the UE index is valid
  ASSERT_NE(ue->get_ue_index(), ue_index_t::invalid);

  // check that the gNB-DU ID has been set
  ASSERT_NE(ue->get_du_id(), gnb_du_id_t::invalid);

  // check that the PCI has been set
  ASSERT_EQ(ue->get_pci(), MIN_PCI);

  // check that the RNTI has been set
  ASSERT_EQ(ue->get_c_rnti(), rnti);

  // check that the Pcell index has been set
  ASSERT_EQ(ue->get_pcell_index(), pcell_index);

  // check that the lookup by PCI and RNTI works
  ASSERT_EQ(ue->get_ue_index(), ue_mng.get_ue_index(ue->get_pci(), ue->get_c_rnti()));

  // check that the number of DU UEs is 1
  ASSERT_EQ(ue_mng.get_nof_du_ues(du_index), 1U);
}

/// Test successful creation of a DU UE
TEST_F(ue_manager_test, when_du_context_valid_then_ue_updated)
{
  du_index_t      du_index    = du_index_t::min;
  ue_index_t      ue_index    = ue_mng.add_ue(du_index);
  rnti_t          rnti        = to_rnti(0x4601);
  du_cell_index_t pcell_index = du_cell_index_t::min;

  auto* ue = ue_mng.set_ue_du_context(ue_index, gnb_du_id_t::min, MIN_PCI, rnti, pcell_index);

  // check that the UE has been created
  ASSERT_NE(ue, nullptr);
  ASSERT_NE(ue_mng.find_du_ue(ue->get_ue_index()), nullptr);

  // check that the UE index is valid
  ASSERT_NE(ue->get_ue_index(), ue_index_t::invalid);

  // check that the gNB-DU ID has been set
  ASSERT_NE(ue->get_du_id(), gnb_du_id_t::invalid);

  // check that the PCI has been set
  ASSERT_EQ(ue->get_pci(), MIN_PCI);

  // check that the RNTI has been set
  ASSERT_EQ(ue->get_c_rnti(), rnti);

  // check that the Pcell index has been set
  ASSERT_EQ(ue->get_pcell_index(), pcell_index);

  // check that the lookup by PCI and RNTI works
  ASSERT_EQ(ue->get_ue_index(), ue_mng.get_ue_index(ue->get_pci(), ue->get_c_rnti()));

  // check that the number of DU UEs is 1
  ASSERT_EQ(ue_mng.get_nof_du_ues(du_index), 1U);
}

/// Test finding invalid UE index
TEST_F(ue_manager_test, when_ue_index_invalid_then_ue_not_found)
{
  du_index_t      du_index    = du_index_t::min;
  rnti_t          rnti        = to_rnti(0x4601);
  du_cell_index_t pcell_index = du_cell_index_t::min;
  ue_index_t      ue_index    = ue_mng.add_ue(du_index, gnb_du_id_t::min, MIN_PCI, rnti, pcell_index);
  auto*           ue          = ue_mng.find_ue(ue_index);

  // check that the UE has been created
  ASSERT_NE(ue, nullptr);

  // check that ue with invalid UE index is not found
  ASSERT_EQ(ue_mng.find_du_ue(ue_index_t::invalid), nullptr);
}

/// Test duplicate UE creation
TEST_F(ue_manager_test, when_rnti_already_exits_then_ue_not_added)
{
  du_index_t      du_index    = du_index_t::min;
  rnti_t          rnti        = to_rnti(0x4601);
  du_cell_index_t pcell_index = du_cell_index_t::min;
  ue_index_t      ue_index    = ue_mng.add_ue(du_index, gnb_du_id_t::min, MIN_PCI, rnti, pcell_index);

  // check that the number of DU UEs is 1
  ASSERT_EQ(ue_mng.get_nof_du_ues(du_index), 1U);

  auto* ue2 = ue_mng.set_ue_du_context(ue_index, gnb_du_id_t::min, MIN_PCI, rnti, pcell_index);

  // check that the UE has not been added
  ASSERT_EQ(ue2, nullptr);
  ASSERT_EQ(ue_mng.get_nof_du_ues(du_index), 1U);
}

/// Test successful removal of a DU UE
TEST_F(ue_manager_test, when_ue_exists_then_removal_successful)
{
  du_index_t      du_index    = du_index_t::min;
  rnti_t          rnti        = to_rnti(0x4601);
  du_cell_index_t pcell_index = du_cell_index_t::min;
  ue_index_t      ue_index    = ue_mng.add_ue(du_index, gnb_du_id_t::min, MIN_PCI, rnti, pcell_index);
  auto*           ue          = ue_mng.find_ue(ue_index);

  ue_mng.remove_ue(ue->get_ue_index());

  // check that the UE has been removed
  ASSERT_EQ(ue_mng.get_nof_du_ues(du_index), 0U);
}

/// Test creation of multiple DU UEs
TEST_F(ue_manager_test, when_multiple_ues_added_then_ues_exist)
{
  du_index_t      du_index    = du_index_t::min;
  du_cell_index_t pcell_index = du_cell_index_t::min;

  // reduce log level to avoid flooding the log
  ue_mng_logger.set_level(srslog::basic_levels::warning);
  test_logger.set_level(srslog::basic_levels::warning);

  for (unsigned it = to_value(rnti_t::MIN_CRNTI);
       it < unsigned(to_value(rnti_t::MIN_CRNTI) + ue_mng.get_ue_config().max_nof_supported_ues);
       it++) {
    rnti_t     rnti     = to_rnti(it);
    ue_index_t ue_index = ue_mng.add_ue(du_index, gnb_du_id_t::min, MIN_PCI, rnti, pcell_index);
    auto*      ue       = ue_mng.find_ue(ue_index);

    // check that the UE has been created
    ASSERT_NE(ue, nullptr);
    ASSERT_NE(ue_mng.find_du_ue(ue->get_ue_index()), nullptr);

    // check that the UE index is valid
    ASSERT_NE(ue->get_ue_index(), ue_index_t::invalid);

    // check that the PCI has been set
    ASSERT_EQ(ue->get_pci(), MIN_PCI);

    // check that the RNTI has been set
    ASSERT_EQ(ue->get_c_rnti(), rnti);

    // check that the lookup by PCI and  RNTI works
    ASSERT_EQ(ue->get_ue_index(), ue_mng.get_ue_index(ue->get_pci(), ue->get_c_rnti()));

    // check that the number of DU UEs is increased
    ASSERT_EQ(ue_mng.get_nof_du_ues(du_index), it - to_value(rnti_t::MIN_CRNTI) + 1);
  }

  // reset log level
  ue_mng_logger.set_level(srslog::basic_levels::debug);

  // check that the maximum number of DU UEs has been reached
  ASSERT_EQ(ue_mng.get_nof_du_ues(du_index), ue_mng.get_ue_config().max_nof_supported_ues);
}

/// Test creation of unsupported number of DU UEs
TEST_F(ue_manager_test, when_more_than_max_ues_added_then_ue_not_created)
{
  du_index_t      du_index    = du_index_t::min;
  du_cell_index_t pcell_index = du_cell_index_t::min;

  // reduce log level to avoid flooding the log
  ue_mng_logger.set_level(srslog::basic_levels::warning);
  test_logger.set_level(srslog::basic_levels::warning);

  for (unsigned it = to_value(rnti_t::MIN_CRNTI);
       it < unsigned(to_value(rnti_t::MIN_CRNTI) + ue_mng.get_ue_config().max_nof_supported_ues);
       it++) {
    rnti_t     rnti     = to_rnti(it);
    ue_index_t ue_index = ue_mng.add_ue(du_index, gnb_du_id_t::min, MIN_PCI, rnti, pcell_index);
    auto*      ue       = ue_mng.find_ue(ue_index);

    // check that the UE has been created
    ASSERT_NE(ue, nullptr);
    ASSERT_NE(ue_mng.find_du_ue(ue->get_ue_index()), nullptr);

    // check that the UE index is valid
    ASSERT_NE(ue->get_ue_index(), ue_index_t::invalid);

    // check that the PCI has been set
    ASSERT_EQ(ue->get_pci(), MIN_PCI);

    // check that the RNTI has been set
    ASSERT_EQ(ue->get_c_rnti(), rnti);

    // check that the lookup by PCI and RNTI works
    ASSERT_EQ(ue->get_ue_index(), ue_mng.get_ue_index(ue->get_pci(), ue->get_c_rnti()));

    // check that the number of DU UEs is increased
    ASSERT_EQ(ue_mng.get_nof_du_ues(du_index), it - to_value(rnti_t::MIN_CRNTI) + 1);
  }

  // reset log level
  ue_mng_logger.set_level(srslog::basic_levels::debug);
  test_logger.set_level(srslog::basic_levels::debug);

  // check that the maximum number of DU UEs has been reached
  ASSERT_EQ(ue_mng.get_nof_du_ues(du_index), ue_mng.get_ue_config().max_nof_supported_ues);

  ue_index_t ue_index = ue_mng.add_ue(du_index);
  ASSERT_EQ(ue_index, ue_index_t::invalid);

  // check that the UE has not been added
  ASSERT_EQ(ue_mng.get_nof_du_ues(du_index), ue_mng.get_ue_config().max_nof_supported_ues);
}
