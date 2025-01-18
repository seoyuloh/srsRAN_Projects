//
// Created by seoyul on 12/11/24.
//

#include "lowphy_tuner_impl.h"

#include "srsran/srslog/srslog.h"
#include "srsran/srsvec/sc_prod.h"

#include <future>
#include <iostream>
namespace srsran {
void lowphy_tuner_impl::tune(baseband_gateway_buffer_writer& buffer)
{
  auto current_gain=attenuation.load(std::memory_order_relaxed);
  // Process amplitude control.
  for (unsigned i_port = 0, i_port_end = buffer.get_nof_channels(); i_port != i_port_end; ++i_port) {
    srsvec::sc_prod(buffer[i_port],current_gain,buffer[i_port]);
  }
}

lowphy_tuner_impl::lowphy_tuner_impl(const lowphy_tuner_config& config) :
  logger(srslog::fetch_basic_logger("Downlink tuner")), sock(config.domain_socket_name)
{
  tuner_thread = std::make_unique<std::thread>([this]() {
    float new_gain;
    do {
      sock >> new_gain;
      if (sock) {
        this->attenuation.store(new_gain, std::memory_order_relaxed);
        logger.info("Attenuation changed to {}", new_gain);
      } else {
        sock.clear();
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } while (new_gain > 0);
  });
  logger.info("Created tuner");
}

std::unique_ptr<lowphy_tuner_impl> lowphy_tuner_impl::create(const lowphy_tuner_config& config)
{
  return std::make_unique<lowphy_tuner_impl>(config);
}


std::unique_ptr<low_phy_tuner> create_lowphy_tuner(const lowphy_tuner_config& config)
{
  if (config.lowphy_tuner_name == "tuner")
    return lowphy_tuner_impl::create(config);
  return nullptr;
}

} // srsran