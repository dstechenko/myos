// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/abort.h>
#include <kernel/assert.h>
#include <kernel/print.h>

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
