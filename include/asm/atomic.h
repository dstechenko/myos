// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_ATOMIC_H
#define ASM_ATOMIC_H
#ifndef __ASSEMBLER__

#include <kernel/types.h>
#include <kernel/assert.h>

#define ATOMIC_INIT(init) { init }

TYPE(atomic32_t, int32_t);

void atomic32_add(atomic32_t *val, int32_t dif);
int32_t atomic32_cmp_swp(atomic32_t *val, int32_t old, int32_t new);

int32_t atomic32_get(const atomic32_t *val) {
  const volatile atomic32_t *ref = val;
  ASSERT(ref);
  return ref->value;
}

void atomic32_set(atomic32_t *val, int32_t new) {
  volatile atomic32_t *ref = val;
  ASSERT(ref);
  ref->value = new;
}

void atomic32_sub(atomic32_t *val, int32_t dif) {
  atomic32_add(val, -dif);
}

void atomic32_inc(atomic32_t *val) {
  atomic32_add(val, 1);
}

void atomic32_dec(atomic32_t *val) {
  atomic32_sub(val, 1);
}

TYPE(atomic64_t, int64_t);

void atomic64_add(atomic64_t *val, int64_t dif);
int64_t atomic64_cmp_swp(atomic64_t *val, int64_t old, int64_t new);

int64_t atomic64_get(const atomic64_t *val) {
  const volatile atomic64_t *ref = val;
  ASSERT(ref);
  return ref->value;
}

void atomic64_set(atomic64_t *val, int64_t new) {
  volatile atomic64_t *ref = val;
  ASSERT(ref);
  ref->value = new;
}

void atomic64_sub(atomic64_t *val, int64_t dif) {
  atomic64_add(val, -dif);
}

void atomic64_inc(atomic64_t *val) {
  atomic64_add(val, 1);
}

void atomic64_dec(atomic64_t *val) {
  atomic64_sub(val, 1);
}

#endif // !__ASSEMBLER__
#endif // !ASM_ATOMIC_H
