// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

.globl cpu_get_level
.globl cpu_get_core
.globl cpu_set_user_pt
.globl cpu_get_user_pt
.globl cpu_set_kernel_pt
.globl cpu_get_kernel_pt

cpu_get_level:
  // Read from the system register for exception levels.
  // EL0 least priv, EL3 the most.
  mrs x0, currentel
  // Shift right by two because the first 2 bits are reserved
  // and are always zero.
  lsr x0, x0, #2
  ret

cpu_get_core:
  // Read from the system register for multiprocessor affinity.
  mrs x0, mpidr_el1
  and x0, x0, #0xFF
  ret

cpu_set_user_pt:
  dsb sy
  msr ttbr0_el1, x0
  isb sy
  tlbi vmalle1is
  ic iallu
  dsb sy
  isb sy
  ret

cpu_get_user_pt:
  mrs x0, ttbr0_el1
  ret

cpu_set_kernel_pt:
  dsb sy
  msr ttbr1_el1, x0
  isb sy
  tlbi vmalle1is
  ic iallu
  dsb sy
  isb sy
  ret

cpu_get_kernel_pt:
  mrs x0, ttbr1_el1
  ret
