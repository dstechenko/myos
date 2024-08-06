// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

.globl cache_inv_data
.globl cache_inv_inst
.globl cache_inv_tlbs

cache_inv_data:
  dc cvau, x0
  ret

cache_inv_inst:
  ic ivau, x0
  ret

cache_inv_tlbs:
  tlbi vmalle1is
  ic iallu
  ret
