// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

.globl cdelay

cycles .req x0
cdelay:
  subs  cycles, cycles, #1
  bne   cdelay
  ret
