/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "rlc_bearer_logger.h"
#include "srsran/adt/byte_buffer.h"
#include "srsran/support/executors/task_executor.h"

namespace srsran {

/// \brief Recycling bin for discarded PDUs that shall be deleted by a different executor off a real-time critical path.
class rlc_discarded_pdu_recycler
{
public:
  rlc_discarded_pdu_recycler(size_t rlc_window_size, rlc_bearer_logger& logger_) : logger(logger_)
  {
    recycle_bin_a.reserve(rlc_window_size);
    recycle_bin_b.reserve(rlc_window_size);
    recycle_bin_c.reserve(rlc_window_size);
  }

  /// \brief Adds a discarded PDU to the recycler which shall be deleted later by another executor
  /// \param pdu The PDU that shall be deleted later
  /// \return True if the PDU was queued for later deletion; False if the PDU was deleted on the spot due to full queue.
  bool add_discarded_pdu(byte_buffer pdu)
  {
    if (recycle_bin_to_fill->size() >= recycle_bin_to_fill->capacity()) {
      // recycle bin is full; delete the PDUs upon return
      return false;
    }
    recycle_bin_to_fill->push_back(std::move(pdu));
    return true;
  }

  /// \brief Delegates the deletion of all stored PDUs to the given task_executor.
  void clear_by_executor(task_executor& executor)
  {
    // Swap recycle bins under a lock
    {
      std::lock_guard<std::mutex> recycle_bin_swap_lock(recycle_bin_swap_mutex);
      std::swap(recycle_bin_to_fill, recycle_bin_to_swap);
    }
    // Redirect recycling of unused byte_buffers to ue_executor
    auto handle_func = [this]() mutable { clear(); };
    if (not executor.execute(std::move(handle_func))) {
      logger.log_error("Failed to delegate deletion of PDUs to given executor.");
    }
  }

private:
  /// \brief Deletes the stored PDUs. This function shall be called from the executor in \c clear_by_executor.
  void clear()
  { // swap recycle bins under a lock
    {
      std::lock_guard<std::mutex> lock(recycle_bin_swap_mutex);
      std::swap(recycle_bin_to_swap, recycle_bin_to_dump);
    }
    // delete all PDUs to return their memory segments to the pool
    recycle_bin_to_dump->clear();
  }

  rlc_bearer_logger& logger;

  /// First recycle bin for discarded PDUs
  std::vector<byte_buffer> recycle_bin_a;
  /// Second recycle bin for discarded PDUs
  std::vector<byte_buffer> recycle_bin_b;
  /// Third recycle bin for discarded PDUs
  std::vector<byte_buffer> recycle_bin_c;
  /// Pointer to an empty recycle bin that shall be filled with discarded PDUs by \c add_discarded_pdu.
  std::vector<byte_buffer>* recycle_bin_to_fill = &recycle_bin_a;
  /// Pointer to a recycle bin that can be swapped with either the recycle_bin_to_fill or the recycle_bin_to_dump.
  std::vector<byte_buffer>* recycle_bin_to_swap = &recycle_bin_b;
  /// Pointer to a recycle bin filled with PDUs that can be deleted (to return their memory segments to the pool).
  std::vector<byte_buffer>* recycle_bin_to_dump = &recycle_bin_c;
  /// Mutex for swapping the recycle bins.
  std::mutex recycle_bin_swap_mutex;
};

} // namespace srsran
