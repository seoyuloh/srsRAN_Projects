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

/// \file
/// \brief Amplitude controller implementation using clipping.

#pragma once

#include "srsran/phy/lower/amplitude_controller/amplitude_controller.h"
#include <span>

namespace srsran {

/// Custom implementation of an amplitude controller.
class amplitude_controller_custom_impl : public amplitude_controller {
public:
  /// Constructor.
  explicit amplitude_controller_custom_impl(float custom_param);

  /// Override the process method to perform amplitude control.
  amplitude_controller_metrics process(span<cf_t> output, span<const cf_t> input) override;

private:
  float custom_param; // Parameter specific to the custom implementation
};

} // namespace srsran


