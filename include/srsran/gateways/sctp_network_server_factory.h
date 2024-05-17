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

#include "sctp_network_gateway.h"
#include "srsran/gateways/sctp_network_server.h"

namespace srsran {

struct sctp_network_server_config {
  sctp_network_node_config          sctp;
  io_broker&                        broker;
  sctp_network_association_factory& association_handler_factory;
};

/// Creates and starts an SCTP network node that can operate both as a server and client and create new SCTP
/// associations.
std::unique_ptr<sctp_network_server> create_sctp_network_server(const sctp_network_server_config& config);

} // namespace srsran