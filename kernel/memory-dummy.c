// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/assert.h>
#include <kernel/config.h>
#include <kernel/memory-ops.h>
#include <kernel/memory.h>
#include <kernel/page.h>
#include <kernel/ptrs.h>

void *memory_alloc(const size_t size, const uint8_t flags) {
  (void)flags;
  (void)size;

  ASSERT(size);
  ASSERT(size <= PAGE_SIZE);

  return (void *)page_get_kernel(/* order = */ 0);
}

void *memory_zalloc(const size_t size, const uint8_t flags) {
  void *obj = memory_alloc(size, flags);

  if (obj) memory_zero(obj, size);

  return obj;
}

void memory_free(const void *ptr) { page_put(PTR_TO_ADR(ptr)); }
