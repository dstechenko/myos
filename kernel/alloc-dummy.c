// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/alloc.h>
#include <kernel/assert.h>
#include <kernel/config.h>
#include <kernel/memory-ops.h>
#include <kernel/page.h>
#include <kernel/ptrs.h>

#if CONFIG_ENABLED(CONFIG_ALLOC_DUMMY)

void *alloc(const size_t size, const uint8_t flags) {
  (void)flags;
  (void)size;

  ASSERT(size);
  ASSERT(size <= PAGE_SIZE);

  if (flags & ALLOC_USER) {
    return (void *)page_get_kernel();
  } else {
    return (void *)page_get_kernel();
  }
}

void *alloc_zero(const size_t size, const uint8_t flags) {
  void *obj = alloc(size, flags);

  if (obj) memzero(obj, size);

  return obj;
}

void alloc_free(const void *ptr) { page_put(PTR_TO_ADR(ptr)); }

#endif  // CONFIG_ENABLED(CONFIG_ALLOC_DUMMY))
