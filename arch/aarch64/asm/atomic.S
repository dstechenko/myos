// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

.globl atomic32_get
.globl atomic32_set
.globl atomic32_add
.globl atomic32_cmp_swp

.globl atomic64_get
.globl atomic64_set
.globl atomic64_add
.globl atomic64_cmp_swp

atomic32_get:
  ldar w1, [x0]
  mov w0, w1
  ret

atomic32_set:
  ldr w2, [x0]
  stlr w1, [x0]
  mov w0, w2
  ret

atomic32_add:
  ldaxr w2, [x0]
  add w3, w2, w1
  stlxr w4, w3, [x0]
  cbnz w4, atomic32_add
  mov w0, w2
  ret

atomic32_cmp_swp:
  ldaxr w3, [x0]
  cmp w3, w1
  bne atomic32_cmp_swp_ret
  stlxr w4, w2, [x0]
  cbnz w4, atomic32_cmp_swp

atomic32_cmp_swp_ret:
  mov w0, w3
  ret

atomic64_get:
  ldar x1, [x0]
  mov x0, x1
  ret

atomic64_set:
  ldr x2, [x0]
  stlr x1, [x0]
  mov x0, x2
  ret

atomic64_add:
  ldaxr x2, [x0]
  add x3, x2, x1
  stlxr w4, x3, [x0]
  cbnz w4, atomic64_add
  mov x0, x2
  ret

atomic64_cmp_swp:
  ldaxr x3, [x0]
  cmp x3, x1
  bne atomic32_cmp_swp_ret
  stlxr w4, x2, [x0]
  cbnz w4, atomic64_cmp_swp

atomic64_cmp_swp_ret:
  mov x0, x3
  ret
