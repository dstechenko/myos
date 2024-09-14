// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

.globl delay_noop
.globl delay_cycles

delay_noop:
  ret

delay_cycles:
  subs  x0, x0, #1
  bne   delay_cycles
  ret
