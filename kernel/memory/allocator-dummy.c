// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/memory/allocator.h>

#include <kernel/memory/ops.h>
#include <kernel/memory/page.h>
#include <kernel/util/assert.h>
#include <kernel/util/ptrs.h>

void *alloc(const size_t size, const uint8_t flags) {
  (void)flags;
  (void)size;

  ASSERT(size);
  ASSERT(size <= PAGE_SIZE);

  if (flags & ALLOC_USER) {
    return (void *)get_kernel_page();
  } else {
    return (void *)get_kernel_page();
  }
}

void *zalloc(const size_t size, const uint8_t flags) {
  void *obj = alloc(size, flags);

  if (obj)
    memzero(obj, size);

  return obj;
}

void free(const void *obj) { put_page(PTR_TO_ADR(obj)); }
