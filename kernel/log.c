// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <drivers/timer.h>
#include <kernel/assert.h>
#include <kernel/log.h>
#include <kernel/print.h>
#include <kernel/spinlock.h>
#include <kernel/types.h>

static spinlock_t log_lock;

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

static void log_timestamp(void) {
  uint64_t timestamp = timer_get_ticks() % 1000;

  if (timestamp < 10) {
    print("00");
  } else if (timestamp < 100) {
    print("0");
  }

  print("%lu ", timestamp);
}

static void log_level(const uint8_t level) { print("%s ", log_level_to_string(level)); }

void log(const uint8_t level, const char *format, ...) {
  irqflags_t flags;
  va_list args;

  ASSERT(format);
  if (CONFIG_LOG_LEVEL < level) return;

  /* flags = spin_lock_irq(&log_lock); */
  log_timestamp();
  log_level(level);
  va_start(args, format);
  print_args(format, &args);
  va_end(args);
  print("\n\r");
  /* spin_unlock_irq(&log_lock, flags); */
}
