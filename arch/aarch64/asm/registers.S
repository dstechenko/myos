// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/registers-defs.h>

.globl registers_get_priv
.globl registers_get_core
.globl registers_set_user_page_table
.globl registers_get_user_page_table
.globl registers_set_kernel_page_table
.globl registers_get_kernel_page_table

.globl registers_test
// TODO(dstechenko): move this file to cpu

registers_get_priv:
  // Read from the system register for exception levels.
  // EL0 least priv, EL3 the most.
  mrs x0, currentel
  // Shift right by two because the first 2 bits are reserved
  // and are always zero.
  lsr x0, x0, #2
  ret

// TODO(dstechenko): only use the first two bits
registers_get_core:
  // Read from the system register for multiprocessor affinity.
  mrs x0, mpidr_el1
  and x0, x0, #0xFF
  ret

registers_set_user_page_table:
  dsb sy
  isb sy
  msr ttbr0_el1, x0
  tlbi vmalle1
// TODO(dstechenko): add config for this
  tlbi vmalle1
  ic iallu
  dsb sy
  isb sy
  ret

registers_get_user_page_table:
  mrs x0, ttbr0_el1
  ret

// TODO(dstechenko): extract  tlb flush as a separate operation

registers_set_kernel_page_table:
  msr ttbr1_el1, x0
  tlbi vmalle1is
  dsb sy
  isb sy
  ret

registers_get_kernel_page_table:
  mrs x0, ttbr1_el1
  ret

registers_test:
  mov x2, 0xD8
  str x1, [x2, x0, LSL #3]
  dsb sy
  sev
  ret
