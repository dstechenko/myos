// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/assert.h>
#include <kernel/memory-ops.h>

void *memory_copy(void *dst, const void *src, const size_t cnt) {
  size_t tmp;
  uint8_t *out = dst;
  const uint8_t *in = src;

  ASSERT(out);
  ASSERT(in);
  ASSERT(cnt);

  for (tmp = 0; tmp < cnt; tmp++) {
    out[tmp] = in[tmp];
  }

  return dst;
}

void *memory_set(void *dst, const uint8_t val, const size_t cnt) {
  size_t tmp;
  uint8_t *out = dst;

  ASSERT(out);
  ASSERT(cnt);

  for (tmp = 0; tmp < cnt; tmp++) {
    out[tmp] = val;
  }

  return dst;
}

void *memory_zero(void *dst, const size_t cnt) { return memory_set(dst, 0, cnt); }
