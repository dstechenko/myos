// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <stdint.h>

#include <kernel/init/entry.h>

void boot_entry(const uint64_t x0, const uint64_t x1, const uint64_t x2,
                const uint64_t x3) {
  // TOOD: do we need to store these for access?
  (void)x0;
  (void)x1;
  (void)x2;
  (void)x3;
  kernel_entry();
}
