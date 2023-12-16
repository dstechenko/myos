// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/log.h>

#include <stdarg.h>

#include <kernel/assert.h>
#include <kernel/print.h>

static const char *log_level_to_string(const uint8_t level) {
  switch (level) {
  case ERROR:
    return "ERR";
  case INFO:
    return "INF";
  case DEBUG:
    return "DBG";
  default:
    ABORT();
  }
  return "ERR";
}

void log(const uint8_t level, const char *format, ...) {
  va_list args;

  ASSERT(format);
  if (CONFIG_LOG_LEVEL < level)
    return;

  // TODO(dstechenko): add timestamps to logs...
  print("[%s] ", log_level_to_string(level));
  va_start(args, format);
  print_args(format, &args);
  va_end(args);
  print("\r\n");
}
