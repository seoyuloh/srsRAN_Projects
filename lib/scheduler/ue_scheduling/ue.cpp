/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include "ue.h"
#include "../logging/scheduler_metrics_handler.h"
#include "../support/dmrs_helpers.h"
#include "../support/prbs_calculator.h"

using namespace srsran;

/// \brief Adapter class to forward HARQ timeout signals to scheduler_metrics_handler.
class harq_timeout_handler_adapter final : public harq_timeout_notifier
{
public:
  harq_timeout_handler_adapter(du_ue_index_t ue_index_, scheduler_metrics_handler& metrics_) :
    ue_index(ue_index_), metrics(metrics_)
  {
  }

  void notify_harq_timeout(bool is_dl) override { metrics.handle_harq_timeout(ue_index, is_dl); }

private:
  du_ue_index_t              ue_index;
  scheduler_metrics_handler& metrics;
};

ue::ue(const scheduler_ue_expert_config&        expert_cfg_,
       const cell_configuration&                cell_cfg_common_,
       const sched_ue_creation_request_message& req,
       scheduler_metrics_handler&               metrics_handler_) :
  ue_index(req.ue_index),
  crnti(req.crnti),
  expert_cfg(expert_cfg_),
  cell_cfg_common(cell_cfg_common_),
  log_channels_configs(req.cfg.lc_config_list),
  sched_request_configs(req.cfg.sched_request_config_list),
  harq_timeout_notif(std::make_unique<harq_timeout_handler_adapter>(ue_index, metrics_handler_)),
  logger(srslog::fetch_basic_logger("SCHED"))
{
  for (unsigned i = 0; i != req.cfg.cells.size(); ++i) {
    ue_du_cells[i] = std::make_unique<ue_cell>(
        ue_index, req.crnti, expert_cfg, cell_cfg_common, req.cfg.cells[i].serv_cell_cfg, *harq_timeout_notif);
    ue_cells.push_back(ue_du_cells[i].get());
  }

  dl_lc_ch_mgr.configure(log_channels_configs);
  ul_lc_ch_mgr.configure(log_channels_configs);
}

void ue::slot_indication(slot_point sl_tx)
{
  for (unsigned i = 0; i != ue_du_cells.size(); ++i) {
    if (ue_du_cells[i] != nullptr) {
      // Clear old HARQs.
      ue_du_cells[i]->harqs.slot_indication(sl_tx);
    }
  }
}

void ue::deactivate()
{
  // Disable DL DRBs.
  for (unsigned lcid = LCID_MIN_DRB; lcid <= LCID_MAX_DRB; lcid++) {
    dl_lc_ch_mgr.set_status((lcid_t)lcid, false);
  }

  // Disable UL SRBs and DRBs.
  for (unsigned lcg_id = 0; lcg_id <= MAX_LCG_ID; lcg_id++) {
    ul_lc_ch_mgr.set_status((lcg_id_t)lcg_id, false);
  }
}

void ue::handle_reconfiguration_request(const sched_ue_reconfiguration_message& msg)
{
  log_channels_configs = msg.cfg.lc_config_list;
  dl_lc_ch_mgr.configure(log_channels_configs);
  ul_lc_ch_mgr.configure(log_channels_configs);

  // Handle removed cells.
  for (unsigned i = 0; i != ue_du_cells.size(); ++i) {
    if (ue_du_cells[i] != nullptr) {
      if (std::none_of(msg.cfg.cells.begin(), msg.cfg.cells.end(), [i](const cell_config_dedicated& c) {
            return c.serv_cell_cfg.cell_index == to_du_cell_index(i);
          })) {
        // TODO: Handle SCell deletions.
      }
    }
  }

  // Handle new cells.
  for (const auto& cell : msg.cfg.cells) {
    if (ue_du_cells[cell.serv_cell_cfg.cell_index] != nullptr) {
      ue_du_cells[cell.serv_cell_cfg.cell_index]->handle_reconfiguration_request(cell.serv_cell_cfg);
    } else {
      // TODO: Handle SCell creation.
    }
  }

  // TODO: Remaining fields.
}

unsigned ue::pending_dl_newtx_bytes() const
{
  return dl_lc_ch_mgr.pending_bytes();
}

unsigned ue::pending_dl_srb0_newtx_bytes() const
{
  unsigned pending_bytes = dl_lc_ch_mgr.pending_bytes(LCID_SRB0);

  if (pending_bytes > 0) {
    // In case SRB0 has data, only allocate SRB0 and CEs.
    return pending_bytes + dl_lc_ch_mgr.pending_ue_con_res_id_ce_bytes();
  }
  return pending_bytes;
}

unsigned ue::pending_ul_newtx_bytes() const
{
  constexpr static unsigned SR_GRANT_BYTES = 512;

  // Sum the last BSRs.
  unsigned pending_bytes = ul_lc_ch_mgr.pending_bytes();

  // Subtract the bytes already allocated in UL HARQs.
  for (const ue_cell* ue_cc : ue_cells) {
    if (pending_bytes == 0) {
      break;
    }
    unsigned harq_bytes = 0;
    for (unsigned i = 0; i != ue_cc->harqs.nof_ul_harqs(); ++i) {
      const ul_harq_process& h_ul = ue_cc->harqs.ul_harq(i);
      if (not h_ul.empty()) {
        harq_bytes += h_ul.last_tx_params().tbs_bytes;
      }
    }
    pending_bytes -= std::min(pending_bytes, harq_bytes);
  }

  // If there are no pending bytes, check if a SR is pending.
  return pending_bytes > 0 ? pending_bytes : (ul_lc_ch_mgr.has_pending_sr() ? SR_GRANT_BYTES : 0);
}

unsigned ue::build_dl_transport_block_info(dl_msg_tb_info& tb_info, unsigned tb_size_bytes)
{
  unsigned total_subpdu_bytes = 0;
  total_subpdu_bytes += allocate_mac_ces(tb_info, dl_lc_ch_mgr, tb_size_bytes);
  total_subpdu_bytes += allocate_mac_sdus(tb_info, dl_lc_ch_mgr, tb_size_bytes - total_subpdu_bytes);
  return total_subpdu_bytes;
}

unsigned ue::build_dl_srb0_transport_block_info(dl_msg_tb_info& tb_info, unsigned tb_size_bytes)
{
  unsigned total_subpdu_bytes = 0;
  total_subpdu_bytes += allocate_ue_con_res_id_mac_ce(tb_info, dl_lc_ch_mgr, tb_size_bytes);
  total_subpdu_bytes += allocate_mac_sdus(tb_info, dl_lc_ch_mgr, tb_size_bytes - total_subpdu_bytes);
  return total_subpdu_bytes;
}
