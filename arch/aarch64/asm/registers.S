// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

.globl registers_get_priv
.globl registers_get_core
.globl registers_set_user_page_table
.globl registers_get_user_page_table
.globl registers_set_kernel_page_table
.globl registers_get_kernel_page_table

registers_get_priv:
  // Read from the system register for exception levels.
  // EL0 least priv, EL3 the most.
  mrs x0, currentel
  // Shift right by two because the first 2 bits are reserved
  // and are always zero.
  lsr x0, x0, #2
  ret

registers_get_core:
  // Read from the system register for multiprocessor affinity.
  mrs x0, mpidr_el1
  and x0, x0, #0xFF
  ret

registers_set_user_page_table:
  // Set lower page table pointer.
  msr ttbr0_el1, x0
  // Invalidate cached table entries right after.
  tlbi vmalle1is
  dsb ish
  isb
  ret

registers_get_user_page_table:
  mrs x0, ttbr0_el1
  ret

registers_set_kernel_page_table:
  // Set lower page table pointer.
  msr ttbr1_el1, x0
  // Invalidate cached table entries right after.
  tlbi vmalle1is
  dsb ish
  isb
  ret

registers_get_kernel_page_table:
  mrs x0, ttbr1_el1
  ret
