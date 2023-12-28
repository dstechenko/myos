// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_ATOMIC_H
#define ASM_ATOMIC_H
#ifndef __ASSEMBLER__

#include <kernel/types.h>

typedef struct {
  int32_t value;
} atomic32_t;

void atomic32_inc(atomic32_t *val);
void atomic32_dec(atomic32_t *val);
void atomic32_swp(atomic32_t *val, int32_t new);
void atomic32_cmp_swp(atomic32_t *val, int32_t old, int32_t new);

typedef struct {
  int64_t value;
} atomic64_t;

void atomic64_inc(atomic64_t *val);
void atomic64_dec(atomic64_t *val);
void atomic64_swp(atomic64_t *val, int64_t new);
void atomic64_cmp_swp(atomic64_t *val, int64_t old, int64_t new);

#endif // !__ASSEMBLER__
#endif // !ASM_ATOMIC_H
