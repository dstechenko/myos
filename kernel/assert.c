// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/abort.h>

#include <kernel/assert.h>
#include <kernel/print.h>

void abort_handle(const char *file, const int line) {
  print("Aborting the execution at %s:%d!\n", file, line);
  abort();
}

void assert_handle(const bool cond, const char *ctx, const char *file, const int line) {
  if (!cond) {
    print("Failed assert on: %s!\n", ctx);
    abort_handle(file, line);
  }
}
