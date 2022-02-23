
#ifndef SRSGNB_PSS_PROCESSOR_DOUBLES_H
#define SRSGNB_PSS_PROCESSOR_DOUBLES_H

#include "srsgnb/phy/upper/signal_processors/pss_processor.h"

namespace srsgnb {

class pss_processor_spy : public pss_processor
{
private:
  struct entry_t {
    config_t              config;
    resource_grid_writer* grid;
  };
  std::vector<entry_t> entries;

public:
  void map(resource_grid_writer& grid, const config_t& args) override
  {
    entry_t entry = {};
    entry.config  = args;
    entry.grid    = &grid;
    entries.emplace_back(entry);
  }
  void                        reset() { entries.clear(); }
  unsigned                    get_nof_entries() const { return entries.size(); }
  const std::vector<entry_t>& get_entries() const { return entries; }
};

} // namespace srsgnb

#endif // SRSGNB_PSS_PROCESSOR_DOUBLES_H
