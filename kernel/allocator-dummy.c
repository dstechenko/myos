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
    // TODO: do proper alloc for users
    return (void *)get_kernel_page();
  } else {
    return (void *)get_kernel_page();
  }
}

void *zalloc(const size_t size, const uint8_t flags) {
  void *obj = alloc(size, flags);

  if (obj)
    // TODO: user zero pages instead of writing
    memzero(obj, size);

  return obj;
}

void free(const void *obj) { put_page(PTR_TO_ADR(obj)); }
