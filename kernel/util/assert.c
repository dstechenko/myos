// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/util/assert.h>

#include <asm/abort.h>
#include <kernel/logging/print.h>

void handle_abort(const char *file, const int line) {
  print("\nAborting the execution at %s:%d!\n", file, line);
  abort();
}

void handle_assert(const bool cond, const char *ctx, const char *file, const int line) {
  if (!cond) {
    print("\nFailed assert on: %s!\n", ctx);
    handle_abort(file, line);
  }
}
