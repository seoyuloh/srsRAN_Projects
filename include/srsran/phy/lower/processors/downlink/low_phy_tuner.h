//
// Created by seoyul on 12/11/24.
//

#ifndef DOWNLINK_TUNER_H
#define DOWNLINK_TUNER_H
#include "srsran/adt/blocking_queue.h"
#include "srsran/gateways/baseband/baseband_gateway_receiver.h"
namespace srsran {

class low_phy_tuner
{
public:
  virtual ~low_phy_tuner() = default;
  virtual void tune(baseband_gateway_buffer_writer& buffer) = 0;
};

class lowphy_tuner_config
{
public:
  std::string lowphy_tuner_name;
  std::string domain_socket_name;
};

std::unique_ptr<low_phy_tuner> create_lowphy_tuner(const lowphy_tuner_config& config);
} // namespace srsran

#endif // DOWNLINK_TUNER_H
