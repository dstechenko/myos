// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/export.h>

delay_noop:
  ret
EXPORT(delay_noop);

delay_cycles:
  subs  x0, x0, #1
  bne   delay_cycles
  ret
EXPORT(delay_cycles);
