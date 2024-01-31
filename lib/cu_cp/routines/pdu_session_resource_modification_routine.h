/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "../du_processor/du_processor_impl_interface.h"
#include "srsran/support/async/async_task.h"
#include "srsran/support/async/eager_async_task.h"

namespace srsran {
namespace srs_cu_cp {

/// \brief Handles the modification of an existing PDU session resources.
/// TODO Add seqdiag
class pdu_session_resource_modification_routine
{
public:
  pdu_session_resource_modification_routine(const cu_cp_pdu_session_resource_modify_request& modify_request_,
                                            du_processor_e1ap_control_notifier&              e1ap_ctrl_notif_,
                                            du_processor_f1ap_ue_context_notifier&           f1ap_ue_ctxt_notif_,
                                            du_processor_rrc_ue_control_message_notifier&    rrc_ue_notifier_,
                                            up_resource_manager&  rrc_ue_up_resource_manager_,
                                            srslog::basic_logger& logger_);

  void operator()(coro_context<async_task<cu_cp_pdu_session_resource_modify_response>>& ctx);

  static const char* name() { return "PDU Session Resource Modification Routine"; }

private:
  void fill_e1ap_bearer_context_modification_request(e1ap_bearer_context_modification_request& e1ap_request);
  void fill_initial_e1ap_bearer_context_modification_request(e1ap_bearer_context_modification_request& e1ap_request);
  bool valid_5qi(const qos_flow_setup_request_item& flow);

  cu_cp_pdu_session_resource_modify_response generate_pdu_session_resource_modify_response(bool success);

  const cu_cp_pdu_session_resource_modify_request modify_request; // the original request

  up_config_update next_config;

  du_processor_e1ap_control_notifier&           e1ap_ctrl_notifier;         // to trigger bearer context setup at CU-UP
  du_processor_f1ap_ue_context_notifier&        f1ap_ue_ctxt_notifier;      // to trigger UE context modification at DU
  du_processor_rrc_ue_control_message_notifier& rrc_ue_notifier;            // to trigger RRC Reconfiguration at UE
  up_resource_manager&                          rrc_ue_up_resource_manager; // to get RRC DRB config
  srslog::basic_logger&                         logger;

  // (sub-)routine requests
  e1ap_bearer_context_modification_request bearer_context_modification_request;
  f1ap_ue_context_modification_request     ue_context_mod_request;
  rrc_reconfiguration_procedure_request    rrc_reconfig_args;

  // (sub-)routine results
  cu_cp_pdu_session_resource_modify_response response_msg;                     // Final routine result.
  f1ap_ue_context_modification_response      ue_context_modification_response; // to inform DU about the new DRBs
  e1ap_bearer_context_modification_response
       bearer_context_modification_response; // to inform CU-UP about the new TEID for UL F1u traffic
  bool rrc_reconfig_result = false;          // the final UE reconfiguration
};

} // namespace srs_cu_cp
} // namespace srsran
