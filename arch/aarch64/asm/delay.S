// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

.globl cdelay
cdelay:
  subs  x0, x0, #1
  bne   cdelay
  ret
