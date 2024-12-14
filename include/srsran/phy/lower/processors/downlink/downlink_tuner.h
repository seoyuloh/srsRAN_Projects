//
// Created by seoyul on 12/11/24.
//

#ifndef DOWNLINK_TUNER_H
#define DOWNLINK_TUNER_H
#include "srsran/adt/blocking_queue.h"
#include "srsran/gateways/baseband/baseband_gateway_receiver.h"
namespace srsran {

class downlink_tuner
{
public:
  virtual ~downlink_tuner() = default;
  virtual void tune(baseband_gateway_buffer_writer& buffer) = 0;
};

class downlink_tuner_config
{
public:
  std::string downlink_tuner_name;
  std::string domain_socket_name;
};

std::unique_ptr<downlink_tuner> create_downlink_tuner(const downlink_tuner_config& config);
} // namespace srsran

#endif // DOWNLINK_TUNER_H
