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

#include "amplitude_controller_custom_impl.h"
#include <iostream>

namespace srsran {

amplitude_controller_metrics amplitude_controller_custom_impl::process(span<cf_t> output, span<const cf_t> input) {
  amplitude_controller_metrics metrics = {};

  float input_power_sum = 0.0f;
  float output_power_sum = 0.0f;
  const float clipping_threshold = 1.0f; // Example clipping threshold
  int clipping_count = 0;

  for (size_t i = 0; i < input.size(); ++i) {
    // Calculate input power
    input_power_sum += std::norm(input[i]);

    // Apply gain and process signal
    output[i] = input[i] * custom_param;

    // Calculate output power
    output_power_sum += std::norm(output[i]);

    // Check for clipping
    if (std::abs(output[i]) > clipping_threshold) {
      ++clipping_count;
    }
  }

  // Populate metrics
  metrics.input_power = input_power_sum / input.size();
  metrics.output_power = output_power_sum / output.size();
  metrics.clipping_count = clipping_count;

  std::cout << "Custom amplitude controller processed data with parameter: " << custom_param << "\n";

  return metrics;
}


} // namespace srsran
