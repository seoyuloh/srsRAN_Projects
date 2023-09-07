/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "cu_up_processor_routine_manager.h"
#include "../routines/initial_cu_up_processor_setup_routine.h"

using namespace srsran;
using namespace srs_cu_cp;

cu_up_processor_routine_manager::cu_up_processor_routine_manager(
    cu_up_processor_context&                   context_,
    cu_up_processor_e1ap_control_notifier&     e1ap_conn_notifier_,
    cu_up_processor_cu_up_management_notifier& cu_cp_notifier_,
    cu_up_task_scheduler&                      task_sched_) :
  context(context_), e1ap_conn_notifier(e1ap_conn_notifier_), cu_cp_notifier(cu_cp_notifier_), task_sched(task_sched_)
{
}

void cu_up_processor_routine_manager::start_initial_cu_up_processor_setup_routine()
{
  task_sched.handle_cu_up_async_task(
      context.cu_up_index,
      launch_async<initial_cu_up_processor_setup_routine>(context, e1ap_conn_notifier, cu_cp_notifier));
}
