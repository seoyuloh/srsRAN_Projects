/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "handover_reconfiguration_routine.h"
#include "../../du_processor/du_processor_impl_interface.h"

using namespace srsran;
using namespace srsran::srs_cu_cp;
using namespace asn1::rrc_nr;

handover_reconfiguration_routine::handover_reconfiguration_routine(
    const rrc_reconfiguration_procedure_request& request_,
    const ue_index_t&                            target_ue_index_,
    du_ue&                                       source_ue_,
    du_processor_f1ap_ue_context_notifier&       source_f1ap_ue_ctxt_notifier_,
    du_processor_cu_cp_notifier&                 cu_cp_notifier_,
    srslog::basic_logger&                        logger_) :
  request(request_),
  target_ue_index(target_ue_index_),
  source_ue(source_ue_),
  source_f1ap_ue_ctxt_notifier(source_f1ap_ue_ctxt_notifier_),
  cu_cp_notifier(cu_cp_notifier_),
  logger(logger_)
{
  srsran_assert(
      source_ue.get_ue_index() != ue_index_t::invalid, "Invalid source UE index {}", source_ue.get_ue_index());
}

void handover_reconfiguration_routine::operator()(coro_context<async_task<bool>>& ctx)
{
  CORO_BEGIN(ctx);

  logger.debug("source_ue={} target_ue={}: \"{}\" initialized", source_ue.get_ue_index(), target_ue_index, name());

  // Get RRC handover reconfiguration context
  ho_reconf_ctxt = source_ue.get_rrc_ue_notifier().get_rrc_ue_handover_reconfiguration_context(request);

  generate_ue_context_modification_request();

  // Call F1AP procedure to send RRC reconfiguration to source UE via UE context modification request
  CORO_AWAIT_VALUE(ue_context_mod_response,
                   source_f1ap_ue_ctxt_notifier.on_ue_context_modification_request(ue_context_mod_request));

  if (ue_context_mod_response.success) {
    CORO_AWAIT_VALUE(procedure_result,
                     cu_cp_notifier.on_handover_reconfiguration_sent(target_ue_index, ho_reconf_ctxt.transaction_id));
  } else {
    logger.debug(
        "source_ue={} target_ue={}: UE context modification failed", source_ue.get_ue_index(), target_ue_index);
  }

  if (procedure_result) {
    logger.debug("source_ue={} target_ue={}: \"{}\" finalized", source_ue.get_ue_index(), target_ue_index, name());
  } else {
    logger.debug("source_ue={} target_ue={}: \"{}\" failed", source_ue.get_ue_index(), target_ue_index, name());
  }

  CORO_RETURN(procedure_result);
}

void handover_reconfiguration_routine::generate_ue_context_modification_request()
{
  ue_context_mod_request.ue_index                 = source_ue.get_ue_index();
  ue_context_mod_request.drbs_to_be_released_list = source_ue.get_up_resource_manager().get_drbs();
  ue_context_mod_request.rrc_container            = ho_reconf_ctxt.rrc_ue_handover_reconfiguration_pdu.copy();
}
