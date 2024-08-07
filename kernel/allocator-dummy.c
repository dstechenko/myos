// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/allocator.h>
#include <kernel/assert.h>
#include <kernel/memory-ops.h>
#include <kernel/page.h>
#include <kernel/ptrs.h>

void *alloc(const size_t size, const uint8_t flags) {
  (void)flags;
  (void)size;

  ASSERT(size);
  ASSERT(size <= PAGE_SIZE);

  if (flags & ALLOC_USER) {
    // TODO(dstechenko): do proper alloc for users
    return (void *)page_get_kernel();
  } else {
    return (void *)page_get_kernel();
  }
}

void *alloc_zero(const size_t size, const uint8_t flags) {
  void *obj = alloc(size, flags);

  if (obj)
    // TODO(dstechenko): user zero pages instead of writing
    memzero(obj, size);

  return obj;
}

void alloc_free(const void *obj) { page_put(PTR_TO_ADR(obj)); }
