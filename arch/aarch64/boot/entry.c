// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <stdint.h>

void kernel_entry();

void boot_entry(uint64_t x0, uint64_t x1, uint64_t x2, uint64_t x3)
{
  (void)x0;
  (void)x1;
  (void)x2;
  (void)x3;
  kernel_entry();
}
