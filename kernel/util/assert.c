// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/util/assert.h>

#include <asm/abort.h>
#include <kernel/logging/log.h>

void handle_abort(void) {
  LOG_ERROR("Aborting the execution...");
  abort();
}

void handle_assert(const bool cond, const char *ctx) {
  if (!cond) {
    LOG_ERROR("Failed assert on: %s", ctx);
    handle_abort();
  }
}
