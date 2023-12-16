// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

.globl delay_nop
.globl delay_cycles

delay_nop:
  nop

delay_cycles:
  subs  x0, x0, #1
  bne   delay_cycles
  ret
