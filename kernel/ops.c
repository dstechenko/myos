// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/ops.h>

#include <kernel/assert.h>

void *memcpy(void *dst, const void *src, size_t cnt) {
  uint8_t *out = (uint8_t *)dst;
  const uint8_t *in = (uint8_t *)src;

  // TODO(dstechenko): fix this
  /* ASSERT(out); */
  /* ASSERT(in); */
  ASSERT(cnt);

  do {
    out[cnt] = in[cnt];
  } while (cnt--);

  return dst;
}

void *memset(void *dst, const uint8_t val, size_t cnt) {
  uint8_t *out = (uint8_t *)dst;

  // TODO(dstechenko): fix this
  /* ASSERT(out); */
  ASSERT(cnt);

  do {
    out[cnt] = val;
  } while (cnt--);

  return dst;
}

void *memzero(void *dst, const size_t cnt) { return memset(dst, 0, cnt); }
