/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "../cu_cp_test_messages.h"
#include "cu_cp_routine_manager_test_helpers.h"
#include "pdu_session_resource_routine_test_helpers.h"
#include "srsran/support/async/async_test_utils.h"
#include "srsran/support/test_utils.h"
#include <gtest/gtest.h>

using namespace srsran;
using namespace srs_cu_cp;

/// Note: Check if UE ID is valid is done by caller. Injection of invalid ue_index results in assertion.

class pdu_session_resource_release_test : public pdu_session_resource_routine_test
{
protected:
  void start_procedure(const cu_cp_pdu_session_resource_release_command& msg,
                       ue_context_outcome_t                              ue_context_modification_outcome,
                       bearer_context_outcome_t                          bearer_context_modification_outcome)
  {
    f1ap_ue_ctxt_mng.set_ue_context_modification_outcome(ue_context_modification_outcome);
    e1ap_bearer_ctxt_mng.set_second_message_outcome(bearer_context_modification_outcome);

    t = routine_mng->start_pdu_session_resource_release_routine(
        msg,
        e1ap_bearer_ctxt_mng,
        f1ap_ue_ctxt_mng,
        rrc_ue_ctrl_notifier,
        cu_cp_notifier,
        ue_task_sched,
        ue_mng.find_ue(msg.ue_index)->get_up_resource_manager());
    t_launcher.emplace(t);
  }

  bool was_pdu_session_resource_release_successful() const
  {
    if (not t.ready()) {
      return false;
    }

    if (t.get().released_pdu_sessions.size() == 0) {
      return false;
    }

    return true;
  }

  bool was_bearer_context_release_command_sent() const
  {
    return e1ap_bearer_ctxt_mng.last_release_command.ue_index != ue_index_t::invalid;
  }

  void setup_pdu_session(ue_index_t ue_index)
  {
    // Setup single PDU session.
    cu_cp_pdu_session_resource_setup_request request = generate_pdu_session_resource_setup(ue_index);
    std::optional<lazy_task_launcher<cu_cp_pdu_session_resource_setup_response>> setup_launcher;

    bearer_context_outcome_t bearer_context_setup_outcome{true, {1}, {}};
    ue_context_outcome_t     ue_context_modification_outcome{true};
    bearer_context_outcome_t bearer_context_modification_outcome{true};

    // Expected results
    e1ap_bearer_ctxt_mng.set_first_message_outcome(bearer_context_setup_outcome);
    f1ap_ue_ctxt_mng.set_ue_context_modification_outcome(ue_context_modification_outcome);
    e1ap_bearer_ctxt_mng.set_second_message_outcome(bearer_context_modification_outcome);
    rrc_ue_ctrl_notifier.set_rrc_reconfiguration_outcome(true);

    async_task<cu_cp_pdu_session_resource_setup_response> setup_task =
        routine_mng->start_pdu_session_resource_setup_routine(
            request,
            security_cfg,
            e1ap_bearer_ctxt_mng,
            f1ap_ue_ctxt_mng,
            rrc_ue_ctrl_notifier,
            cu_cp_notifier,
            ue_mng.find_ue(request.ue_index)->get_task_sched(),
            ue_mng.find_ue(request.ue_index)->get_up_resource_manager());
    setup_launcher.emplace(setup_task);
  }

  async_task<cu_cp_pdu_session_resource_release_response>                        t;
  std::optional<lazy_task_launcher<cu_cp_pdu_session_resource_release_response>> t_launcher;
};

TEST_F(pdu_session_resource_release_test, when_ue_context_modification_failure_received_then_release_succeeds)
{
  // Test Preamble.
  ue_index_t ue_index = ue_mng.add_ue(du_index_t::min);
  setup_pdu_session(ue_index);

  cu_cp_pdu_session_resource_release_command command = generate_pdu_session_resource_release(ue_index);

  // Start PDU SESSION RESOURCE RELEASE routine.
  bearer_context_outcome_t bearer_context_modification_outcome{false};
  this->start_procedure(command, {true}, bearer_context_modification_outcome);

  // nothing has failed to be release
  ASSERT_TRUE(was_pdu_session_resource_release_successful());
}

TEST_F(pdu_session_resource_release_test, when_bearer_context_modification_failure_received_then_release_succeeds)
{
  // Test Preamble.
  ue_index_t ue_index = ue_mng.add_ue(du_index_t::min);
  setup_pdu_session(ue_index);

  cu_cp_pdu_session_resource_release_command command = generate_pdu_session_resource_release(ue_index);

  // Start PDU SESSION RESOURCE RELEASE routine.
  bearer_context_outcome_t bearer_context_modification_outcome{true};
  this->start_procedure(command, {true}, bearer_context_modification_outcome);

  // nothing has failed to setup
  ASSERT_TRUE(was_pdu_session_resource_release_successful());
}

/// Test handling of PDU session release command without any release item.
TEST_F(pdu_session_resource_release_test, when_empty_pdu_session_release_command_received_then_release_fails)
{
  // Test Preamble.
  ue_index_t                                 ue_index = ue_mng.add_ue(du_index_t::min);
  cu_cp_pdu_session_resource_release_command command  = {}; // empty message
  command.ue_index                                    = ue_index;

  // Start PDU SESSION RESOURCE SETUP routine.
  bearer_context_outcome_t bearer_context_modification_outcome{true};
  this->start_procedure(command, {true}, bearer_context_modification_outcome);

  // it should be ready immediately
  ASSERT_TRUE(t.ready());

  // Nothing has been set up or failed
  ASSERT_FALSE(was_pdu_session_resource_release_successful());
}

TEST_F(pdu_session_resource_release_test, when_all_sub_actions_succeed_then_release_succeeds)
{
  // Test Preamble.
  ue_index_t ue_index = ue_mng.add_ue(du_index_t::min);
  setup_pdu_session(ue_index);

  cu_cp_pdu_session_resource_release_command command = generate_pdu_session_resource_release(ue_index);

  // Start PDU SESSION RESOURCE RELEASE routine.
  start_procedure(command, {true}, {true});

  // All released.
  ASSERT_TRUE(was_pdu_session_resource_release_successful());
}

TEST_F(pdu_session_resource_release_test, when_only_pdu_session_released_then_bearer_context_release_command_sent)
{
  // Test Preamble.
  ue_index_t ue_index = ue_mng.add_ue(du_index_t::min);
  setup_pdu_session(ue_index);

  cu_cp_pdu_session_resource_release_command command = generate_pdu_session_resource_release(ue_index);

  // Start PDU SESSION RESOURCE RELEASE routine.
  start_procedure(command, {true}, {true});

  ASSERT_TRUE(was_bearer_context_release_command_sent());

  // All released.
  ASSERT_TRUE(was_pdu_session_resource_release_successful());
}