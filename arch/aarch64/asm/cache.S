// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/export.h>

cache_inv_data:
  dc civac, x0
  ret
EXPORT(cache_inv_data);

cache_inv_inst:
  ic ivau, x0
  ret
EXPORT(cache_inv_inst);

cache_inv_tlbs:
  tlbi vmalle1is
  ic iallu
  ret
EXPORT(cache_inv_tlbs);
