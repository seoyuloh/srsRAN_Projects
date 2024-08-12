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

#include "du_bearer_resource_manager.h"
#include "du_pucch_resource_manager.h"
#include "du_ran_resource_manager.h"
#include "srsran/ran/qos/five_qi.h"

namespace srsran {
namespace srs_du {

class du_ran_resource_manager_impl;

class du_ue_ran_resource_updater_impl final : public ue_ran_resource_configurator::resource_updater
{
public:
  du_ue_ran_resource_updater_impl(du_ue_resource_config*        cell_cfg_,
                                  du_ran_resource_manager_impl& parent_,
                                  du_ue_index_t                 ue_index_);
  du_ue_ran_resource_updater_impl(const du_ue_ran_resource_updater_impl&)            = delete;
  du_ue_ran_resource_updater_impl(const du_ue_ran_resource_updater_impl&&)           = delete;
  du_ue_ran_resource_updater_impl& operator=(const du_ue_ran_resource_updater_impl&) = delete;
  du_ue_ran_resource_updater_impl& operator=(du_ue_ran_resource_updater_impl&&)      = delete;
  ~du_ue_ran_resource_updater_impl() override;

  du_ue_resource_update_response update(du_cell_index_t                       pcell_index,
                                        const f1ap_ue_context_update_request& upd_req,
                                        const du_ue_resource_config*          reestablished_context) override;

  const du_ue_resource_config& get() override { return *cell_grp; }

private:
  du_ue_resource_config*        cell_grp;
  du_ran_resource_manager_impl* parent;
  du_ue_index_t                 ue_index;
};

class du_ran_resource_manager_impl : public du_ran_resource_manager
{
public:
  du_ran_resource_manager_impl(span<const du_cell_config>                cell_cfg_list_,
                               const scheduler_expert_config&            scheduler_cfg,
                               const std::map<srb_id_t, du_srb_config>&  srbs,
                               const std::map<five_qi_t, du_qos_config>& qos);
  du_ran_resource_manager_impl(du_ran_resource_manager_impl&&)                 = delete;
  du_ran_resource_manager_impl(const du_ran_resource_manager_impl&)            = delete;
  du_ran_resource_manager_impl& operator=(du_ran_resource_manager_impl&&)      = delete;
  du_ran_resource_manager_impl& operator=(const du_ran_resource_manager_impl&) = delete;

  expected<ue_ran_resource_configurator, std::string>
  create_ue_resource_configurator(du_ue_index_t ue_index, du_cell_index_t pcell_index) override;

  /// \brief Updates a UE's cell configuration context based on the F1 UE Context Update request.
  ///
  /// UE Context updates may include the addition of new bearers, reservation of PUCCH Resources for Scheduling
  /// Requests or CSI, etc.
  /// \param ue_index Id of the UE whose context is being updated.
  /// \param pcell_idx DU Cell Id of the UE's PCell.
  /// \param upd_req UE Context Update Request received by the F1AP-DU from the CU.
  /// \param reestablished_context Optional parameter to provide the previous context of the UE, in case of an RRC
  /// Reestablishment.
  /// \return Result of the context update.
  du_ue_resource_update_response update_context(du_ue_index_t                         ue_index,
                                                du_cell_index_t                       pcell_idx,
                                                const f1ap_ue_context_update_request& upd_req,
                                                const du_ue_resource_config*          reestablished_context);

  /// \brief Deallocates the RAN resources taken by the UE, so that they can be used by future UEs.
  ///
  /// \param ue_index Id of the UE whose context is being deallocated.
  void deallocate_context(du_ue_index_t ue_index);

private:
  error_type<std::string>
       allocate_cell_resources(du_ue_index_t ue_index, du_cell_index_t cell_index, serv_cell_index_t serv_cell_index);
  void deallocate_cell_resources(du_ue_index_t ue_index, serv_cell_index_t serv_cell_index);

  span<const du_cell_config> cell_cfg_list;
  srslog::basic_logger&      logger;

  struct ue_res_item {
    du_ue_resource_config cg_cfg;
  };

  /// Current UE Resource Allocations.
  slotted_array<ue_res_item, MAX_NOF_DU_UES, false> ue_res_pool;

  /// Allocator of UE PUCCH resources.
  du_pucch_resource_manager pucch_res_mng;

  /// Allocator of UE bearer resources.
  du_bearer_resource_manager bearer_res_mng;
};

} // namespace srs_du
} // namespace srsran
