//
// Created by seoyul on 12/11/24.
//

#include "downlink_tuner_impl.h"
#include "srsran/srsvec/sc_prod.h"

#include <future>
#include <iostream>
namespace srsran {
void downlink_tuner_impl::tune(baseband_gateway_buffer_writer& buffer)
{
  auto current_gain=attenuation.load(std::memory_order_relaxed);
  // Process amplitude control.
  for (unsigned i_port = 0, i_port_end = buffer.get_nof_channels(); i_port != i_port_end; ++i_port) {
    srsvec::sc_prod(buffer[i_port],current_gain,buffer[i_port]);
  }
}

 downlink_tuner_impl::downlink_tuner_impl()
{
  tuner_thread=std::make_unique<std::thread>([this]() {
    float new_gain;
    do {
      std::cin>>new_gain;
      this->attenuation.store(new_gain, std::memory_order_relaxed);
    }while (new_gain>0);
  });
}

std::unique_ptr<downlink_tuner_impl> downlink_tuner_impl::create()
{
  return std::make_unique<downlink_tuner_impl>();
}


std::unique_ptr<downlink_tuner> create_downlink_tuner(const downlink_tuner_config& config)
{
  if (config.downlink_tuner_name=="tuner")
    return downlink_tuner_impl::create();
  return nullptr;
}

} // srsran