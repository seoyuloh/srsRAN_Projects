//
// Created by seoyul on 12/11/24.
//

#ifndef DOWNLINK_TUNER_IMPL_H
#define DOWNLINK_TUNER_IMPL_H
#include <fstream>
#include "srsran/adt/blocking_queue.h"
#include "srsran/gateways/baseband/baseband_gateway_receiver.h"
#include "srsran/gateways/baseband/buffer/baseband_gateway_buffer_dynamic.h"
#include "srsran/phy/lower/processors/downlink/downlink_tuner.h"
#include "srsran/srslog/logger.h"

namespace srsran {

class downlink_tuner_impl : public downlink_tuner
{
public:
  void                                                      tune(baseband_gateway_buffer_writer& buffer) override;
  [[nodiscard]] static std::unique_ptr<downlink_tuner_impl> create(const downlink_tuner_config& config);
  explicit downlink_tuner_impl(const downlink_tuner_config&);
  downlink_tuner_impl() = delete;
private:
  std::unique_ptr<std::thread> tuner_thread;
  std::atomic<double>          attenuation = 1.0;
  std::atomic_bool             monitoring  = false;
  srslog::basic_logger& logger;
  std::ifstream sock;
};

} // namespace srsran

#endif // DOWNLINK_TUNER_H
