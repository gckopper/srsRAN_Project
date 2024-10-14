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

#pragma once

#include "apps/units/flexible_du/du_high/du_high_config.h"
#include "apps/units/flexible_du/du_low/du_low_config.h"
#include "apps/units/flexible_du/fapi/fapi_config.h"
#include "apps/units/flexible_du/split_8/helpers/ru_sdr_config.h"

namespace srsran {

/// Split 8 DU unit configuration.
struct split_8_du_unit_config {
  /// DU high configuration.
  du_high_parsed_config du_high_cfg;
  /// DU low configuration.
  du_low_unit_config du_low_cfg;
  /// FAPI configuration.
  fapi_unit_config fapi_cfg;
  /// Radio Unit configuration.
  ru_sdr_unit_config ru_cfg;
};

} // namespace srsran