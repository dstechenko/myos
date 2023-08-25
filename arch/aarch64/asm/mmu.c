// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/mmu.h>

void handle_data_abort(uint64_t far, uint64_t esr) {
  (void)far;
  (void)esr;
}
