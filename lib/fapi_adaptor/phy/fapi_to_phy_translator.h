/*
 *
 * Copyright 2013-2022 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "srsgnb/fapi/messages.h"
#include "srsgnb/fapi/slot_message_gateway.h"
#include "srsgnb/phy/upper/channel_processors/pdsch_processor.h"
#include <mutex>

namespace srsgnb {

class downlink_processor;
class downlink_processor_pool;
class resource_grid_pool;
class uplink_request_processor;

namespace fapi_adaptor {

/// \brief FAPI-to-PHY message translator.
///
/// This class receives slot-based FAPI messages and translates them into PHY specific data types, which can then be
/// processed by the upper PHY.
///
/// Translating and processing slot-based FAPI messages involves converting them to the suitable data types for the PHY
/// layer, validation of the contents for each incoming message and selecting and reserving resources in the upper PHY
/// to process the messages.
///
/// \note This class is thread safe and allows calling the \ref handle_new_slot method and the message handlers from
/// different threads.
/// \note The translator assumes that only one message of each type can be received within a slot. Receiving multiple
/// messages of the same type in one slot results in undefined behavior.
class fapi_to_phy_translator : public fapi::slot_message_gateway
{
  /// \brief Slot-based upper PHY controller.
  ///
  /// Takes care of the opening and closing procedures required by the upper PHY within each slot.
  ///
  /// \note This class follows the RAII (resource acquisition is initialization) programming principle.
  /// \note The lifetime of any instantiation of this class is meant to be a single slot.
  class slot_based_upper_phy_controller
  {
    slot_point                                 slot;
    std::reference_wrapper<downlink_processor> dl_processor;

  public:
    slot_based_upper_phy_controller();

    slot_based_upper_phy_controller(downlink_processor_pool& dl_processor_pool,
                                    resource_grid_pool&      rg_pool,
                                    slot_point               slot,
                                    unsigned                 sector_id);

    slot_based_upper_phy_controller(slot_based_upper_phy_controller&& other) = delete;

    slot_based_upper_phy_controller& operator=(slot_based_upper_phy_controller&& other);

    ~slot_based_upper_phy_controller();

    downlink_processor*       operator->() { return &dl_processor.get(); }
    const downlink_processor* operator->() const { return &dl_processor.get(); }
  };

public:
  /// \brief Constructor for the FAPI-to-PHY translator.
  ///
  /// \param[in] sector_id Sector identifier.
  /// \param[in] dl_processor_pool Downlink processor pool that will be used to process PDUs.
  /// \param[in] rg_pool Resource grid pool that will be used to process PDUs.
  /// \param[in] ul_request_processor Uplink request processor.
  /// \param[in] scs_common Common subcarrier spacing, as per TS38.331 Section 6.2.2.
  /// \param[in] prach_tlv PRACH configuration TLV.
  /// \param[in] carrier_tlv Carrier configuration TLV.
  fapi_to_phy_translator(unsigned                    sector_id,
                         downlink_processor_pool&    dl_processor_pool,
                         resource_grid_pool&         rg_pool,
                         uplink_request_processor&   ul_request_processor,
                         subcarrier_spacing          scs_common,
                         const fapi::prach_config&   prach_tlv,
                         const fapi::carrier_config& carrier_tlv) :
    sector_id(sector_id),
    dl_processor_pool(dl_processor_pool),
    rg_pool(rg_pool),
    ul_request_processor(ul_request_processor),
    scs_common(scs_common),
    prach_tlv(prach_tlv),
    carrier_tlv(carrier_tlv)
  {
  }

  // See interface for documentation.
  void dl_tti_request(const fapi::dl_tti_request_message& msg) override;

  // See interface for documentation.
  void ul_tti_request(const fapi::ul_tti_request_message& msg) override;

  // See interface for documentation.
  void ul_dci_request(const fapi::ul_dci_request_message& msg) override;

  // See interface for documentation.
  void tx_data_request(const fapi::tx_data_request_message& msg) override;

  /// \brief Handles a new slot.
  ///
  /// Handling a new slot consists of the following steps.
  /// - Finish processing the PDUs from the previous slot.
  /// - Update the current slot value to the new one.
  /// - Obtain a new resource grid and a new downlink processor from the corresponding pools.
  /// - Configure the downlink processor with the new resource grid.
  /// - Reset the contents of the PDSCH PDU repository.
  ///
  /// \param[in] slot Identifies the new slot.
  /// \note This method is thread safe and may be called from different threads.
  void handle_new_slot(slot_point slot);

private:
  /// Sector identifier.
  const unsigned sector_id;
  /// Downlink processor pool.
  downlink_processor_pool& dl_processor_pool;
  /// Resource grid pool.
  resource_grid_pool& rg_pool;
  /// Uplink request processor.
  uplink_request_processor& ul_request_processor;
  /// Current slot task controller.
  slot_based_upper_phy_controller current_slot_controller;
  /// PDSCH PDU repository.
  static_vector<pdsch_processor::pdu_t, fapi::dl_tti_request_message::MAX_NUM_PDUS> pdsch_pdu_repository;
  /// Protects concurrent access to shared variables.
  //: TODO: make this lock free.
  std::mutex mutex;
  // :TODO: these variables should be asked to the cell configuration. Remove them when they're available.
  /// Common subcarrier spacing.
  const subcarrier_spacing scs_common;
  /// PRACH configuration.
  const fapi::prach_config prach_tlv;
  /// Carrier configuration.
  const fapi::carrier_config carrier_tlv;
};

} // namespace fapi_adaptor
} // namespace srsgnb
