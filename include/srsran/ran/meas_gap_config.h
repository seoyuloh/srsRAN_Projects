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

#include "srsran/ran/slot_point.h"
#include "srsran/ran/subcarrier_spacing.h"

namespace srsran {

/// Measurement Gap Repetition Period (MGRP) in msec, as per TS 38.331.
enum class meas_gap_repetition_period : uint8_t { ms20 = 20, ms40 = 40, ms80 = 80, ms160 = 160 };

/// Measurement Gap Length (MGL) in msec, as per TS 38.331.
enum class meas_gap_length : uint8_t { ms1dot5, ms3, ms3dot5, ms4, ms5dot5, ms6 };

/// Configuration of a Measurement Gap as per TS 38.331, GapConfig.
struct meas_gap_config {
  /// Gap offset of the pattern in msec. Value must be between 0 and gap repetition period - 1.
  unsigned offset;
  /// Measurement Gap Length (MGL).
  meas_gap_length mgl;
  /// Measurement Gap Repetition Period (MGRP).
  meas_gap_repetition_period mgrp;
};

/// Convert measurement gap length into a float in milliseconds.
inline unsigned meas_gap_length_to_msec(meas_gap_length len)
{
  constexpr static std::array<float, 6> vals{1.5, 3, 3.5, 4, 5.5, 6};
  return vals[static_cast<unsigned>(len)];
}

/// Determines whether a slot is inside the measurement gap.
inline bool is_inside_meas_gap(const meas_gap_config& gap, slot_point sl)
{
  unsigned period_slots = static_cast<uint8_t>(gap.mgrp) * sl.nof_slots_per_subframe();
  unsigned length_slots = meas_gap_length_to_msec(gap.mgl) * sl.nof_slots_per_subframe();
  unsigned slot_mod     = sl.to_uint() % period_slots;
  return slot_mod <= length_slots;
}

} // namespace srsran