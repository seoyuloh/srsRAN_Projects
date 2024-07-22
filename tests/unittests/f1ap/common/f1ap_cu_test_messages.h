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

#include "tests/test_doubles/f1ap/f1ap_test_messages.h"
#include "srsran/asn1/f1ap/f1ap_ies.h"
#include "srsran/f1ap/common/f1ap_ue_id.h"
#include "srsran/f1ap/cu_cp/f1ap_cu.h"
#include <optional>

namespace srsran {
namespace srs_cu_cp {

/// \brief Generates dummy F1AP Initial UL RRC Transfer message without DU to CU container.
f1ap_message generate_init_ul_rrc_message_transfer_without_du_to_cu_container(gnb_du_ue_f1ap_id_t du_ue_id,
                                                                              rnti_t              crnti);

/// \brief Generates dummy F1AP Initial UL RRC TRANSFER message.
f1ap_message generate_init_ul_rrc_message_transfer(gnb_du_ue_f1ap_id_t du_ue_id,
                                                   rnti_t              crnti           = to_rnti(0x4601),
                                                   byte_buffer         du2cu_container = {});

/// \brief Generates dummy F1AP UL RRC TRANSFER message.
f1ap_message generate_ul_rrc_message_transfer(gnb_cu_ue_f1ap_id_t cu_ue_id,
                                              gnb_du_ue_f1ap_id_t du_ue_id,
                                              srb_id_t            srb_id = srb_id_t::srb1,
                                              byte_buffer rrc_container = byte_buffer::create({0x1, 0x2, 0x3}).value());

/// \brief Generates dummy F1AP UE CONTEXT RELEASE COMPLETE message.
f1ap_message generate_ue_context_release_complete(gnb_cu_ue_f1ap_id_t cu_ue_id, gnb_du_ue_f1ap_id_t du_ue_id);

/// \brief Generates dummy F1AP UE CONTEXT SETUP REQUEST message.
f1ap_message generate_ue_context_setup_request(gnb_cu_ue_f1ap_id_t cu_ue_id, gnb_du_ue_f1ap_id_t du_ue_id);

/// \brief Generates dummy F1AP UE CONTEXT SETUP RESPONSE message.
f1ap_message generate_ue_context_setup_response(
    gnb_cu_ue_f1ap_id_t   cu_ue_id,
    gnb_du_ue_f1ap_id_t   du_ue_id,
    std::optional<rnti_t> crnti = std::nullopt,
    byte_buffer           cell_group_config =
        make_byte_buffer("5c02b091117aec701061e000b1c03544cde4a20c7c080408c008241000100000").value());

/// \brief Generates dummy F1AP UE CONTEXT SETUP FAILURE message.
f1ap_message generate_ue_context_setup_failure(gnb_cu_ue_f1ap_id_t cu_ue_id, gnb_du_ue_f1ap_id_t du_ue_id);

/// \brief Generates dummy CU-CP UE CONTEXT MODIFICATION REQUEST message.
f1ap_ue_context_modification_request generate_ue_context_modification_request(ue_index_t ue_index);

/// \brief Generates dummy F1AP UE CONTEXT MODIFICATION RESPONSE message.
f1ap_message
generate_ue_context_modification_response(gnb_cu_ue_f1ap_id_t          cu_ue_id,
                                          gnb_du_ue_f1ap_id_t          du_ue_id,
                                          rnti_t                       crnti               = to_rnti(0x4601),
                                          const std::vector<drb_id_t>& drbs_setup_mod_list = {drb_id_t::drb1},
                                          const std::vector<drb_id_t>& drbs_modified_list  = {});

/// \brief Generates dummy F1AP UE CONTEXT MODIFICATION FAILURE message.
f1ap_message generate_ue_context_modification_failure(gnb_cu_ue_f1ap_id_t cu_ue_id, gnb_du_ue_f1ap_id_t du_ue_id);

/// \brief Generate a dummy Paging message.
cu_cp_paging_message generate_paging_message();

} // namespace srs_cu_cp
} // namespace srsran
