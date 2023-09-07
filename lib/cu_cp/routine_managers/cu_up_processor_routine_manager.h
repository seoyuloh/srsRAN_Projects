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

#include "../task_schedulers/cu_up_task_scheduler.h"
#include "srsran/cu_cp/cu_up_processor.h"
#include "srsran/support/async/async_task.h"
#include "srsran/support/async/async_task_loop.h"

namespace srsran {
namespace srs_cu_cp {

/// \brief Service provided by CU-UP Processor to handle routines.
class cu_up_processor_routine_manager
{
public:
  explicit cu_up_processor_routine_manager(cu_up_processor_context&                   context_,
                                           cu_up_processor_e1ap_control_notifier&     e1ap_conn_notifier_,
                                           cu_up_processor_cu_up_management_notifier& cu_cp_notifier_,
                                           cu_up_task_scheduler&                      task_sched_);
  ~cu_up_processor_routine_manager() = default;

  void start_initial_cu_up_processor_setup_routine();

private:
  cu_up_processor_context&                   context;
  cu_up_processor_e1ap_control_notifier&     e1ap_conn_notifier;
  cu_up_processor_cu_up_management_notifier& cu_cp_notifier;
  cu_up_task_scheduler&                      task_sched;
};

} // namespace srs_cu_cp
} // namespace srsran
