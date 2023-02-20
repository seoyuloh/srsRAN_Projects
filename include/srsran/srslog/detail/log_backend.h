/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

#include "srsran/srslog/shared_types.h"
#include "fmt/core.h"

namespace srslog {

namespace detail {

struct log_entry;

/// The log backend receives generated log entries from the application. Each
/// entry gets distributed to the corresponding sinks.
/// NOTE: Thread safe class.
class log_backend
{
public:
  virtual ~log_backend() = default;

  /// Starts the processing of incoming log entries.
  /// NOTE: Calling this function more than once has no side effects.
  virtual void start(backend_priority priority = backend_priority::normal) = 0;

  /// Allocates a dyn_arg_store and returns a pointer to it on success, otherwise returns nullptr.
  virtual fmt::dynamic_format_arg_store<fmt::format_context>* alloc_arg_store() = 0;

  /// Pushes a log entry into the backend. Returns true on success, otherwise
  /// false.
  virtual bool push(log_entry&& entry) = 0;

  /// Returns true when the backend has been started, otherwise false.
  virtual bool is_running() const = 0;
};

} // namespace detail

} // namespace srslog