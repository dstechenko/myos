// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/util/assert.h>

#include <asm/abort.h>
#include <kernel/log.h>

void handle_abort(void) {
  log_error("Aborting the execution...");
  abort();
}

void handle_assert(const bool cond, const char *ctx) {
  if (!cond) {
    log_error("Failed assert on: %s", ctx);
    handle_abort();
  }
}
