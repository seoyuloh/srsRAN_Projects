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

#include "srsran/adt/byte_buffer.h"

struct sockaddr_storage;

namespace srsran {

class io_broker;

/// \brief Generic network gateway interfaces to connect components to the outside world.

/// \brief Common parameters to all network gateways. Specific gateway
/// implementations will further specify parameters according to their
/// needs.
struct common_network_gateway_config {
  std::string bind_interface;
  /// Bind address to use for the SCTP socket. If left empty, the SCTP node can only operate as a client.
  std::string bind_address;
  int         bind_port         = 0;
  bool        non_blocking_mode = false;
  unsigned    rx_timeout_sec    = 1; /// Socket received timeout in seconds
  bool        reuse_addr        = false;
};

/// \brief Interface to inform upper layers about reception of new PDUs.
class network_gateway_data_notifier
{
public:
  virtual ~network_gateway_data_notifier() = default;

  /// \brief This callback is invoked on each received PDU.
  /// \param[in]  put Byte-buffer with new PDU.
  virtual void on_new_pdu(byte_buffer pdu) = 0;
};

/// \brief Interface to inform upper layers about reception of new PDUs and source address.
class network_gateway_data_notifier_with_src_addr
{
public:
  virtual ~network_gateway_data_notifier_with_src_addr() = default;

  /// \brief This callback is invoked on each received PDU.
  /// \param[in]  put Byte-buffer with new PDU.
  /// \param[in]  Source address
  virtual void on_new_pdu(byte_buffer pdu, const sockaddr_storage& src_addr) = 0;
};

/// \brief Interface to control common parameters to all
/// network gateways, such as create(), bind(), etc.
/// Gateway specializations should add specific methods as required.
class network_gateway_controller
{
public:
  virtual ~network_gateway_controller() = default;

  /// \brief Create and bind the configured address and port.
  virtual bool create_and_bind() = 0;

  /// \brief Trigger receive call on socket.
  virtual void receive() = 0;

  /// \brief Return socket file descriptor.
  virtual int get_socket_fd() = 0;

  /// \brief Subscribe GW to IO broker for automatic notification of events.
  virtual bool subscribe_to(io_broker& broker) = 0;
};

} // namespace srsran
