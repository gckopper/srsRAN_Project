/*
 * Copyright 2013-2022 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "../cell/resource_grid.h"
#include "../pdcch_scheduling/pdcch_resource_allocator.h"
#include "../policy/ue_allocator.h"
#include "../pucch_scheduling/pucch_scheduler.h"

namespace srsgnb {

/// This class implements the ue_pdsch_allocator and ue_pusch_allocator interfaces, namely the methods to allocate
/// PDSCH and PUSCH grants in different cells, and the methods to fetch the current gNB resource grid DL and UL states.
class ue_cell_grid_allocator : public ue_pdsch_allocator, public ue_pusch_allocator
{
public:
  ue_cell_grid_allocator(ue_list& ues_, srslog::basic_logger& logger_);

  /// Adds a new cell to the UE allocator.
  void add_cell(du_cell_index_t           cell_index,
                pdcch_resource_allocator& pdcch_sched,
                pucch_allocator&          pucch_alloc,
                cell_resource_allocator&  cell_alloc);

  size_t nof_cells() const { return cells.size(); }

  const cell_slot_resource_grid& dl_resource_grid(du_cell_index_t cell_index, unsigned k0) const override
  {
    return get_res_alloc(cell_index)[k0].dl_res_grid;
  }

  bool allocate_dl_grant(const ue_pdsch_grant& grant) override;

  const cell_slot_resource_grid& ul_resource_grid(du_cell_index_t cell_index, unsigned k2) const override
  {
    return get_res_alloc(cell_index)[k2].ul_res_grid;
  }

  bool allocate_ul_grant(const ue_pusch_grant& grant) override;

private:
  struct cell_t {
    du_cell_index_t           cell_index;
    pdcch_resource_allocator* pdcch_sched;
    pucch_allocator*          pucch_alloc;
    cell_resource_allocator*  cell_alloc;
  };

  bool has_cell(du_cell_index_t cell_index) const { return cells.contains(cell_index); }

  pdcch_resource_allocator& get_pdcch_sched(du_cell_index_t cell_index) { return *cells[cell_index].pdcch_sched; }

  pucch_allocator& get_pucch_alloc(du_cell_index_t cell_index) { return *cells[cell_index].pucch_alloc; }

  cell_resource_allocator&       get_res_alloc(du_cell_index_t cell_index) { return *cells[cell_index].cell_alloc; }
  const cell_resource_allocator& get_res_alloc(du_cell_index_t cell_index) const
  {
    return *cells[cell_index].cell_alloc;
  }

  ue_list&              ues;
  srslog::basic_logger& logger;

  slot_array<cell_t, MAX_NOF_DU_CELLS> cells;
};

} // namespace srsgnb
