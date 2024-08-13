// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/alloc.h>
#include <kernel/config.h>
#include <kernel/types.h>

#if CONFIG_ENABLED(CONFIG_ALLOC_BUDDY)

void *alloc(const size_t size, const uint8_t flags) {
  (void)size;
  (void)flags;
  return NULL;
}

void *alloc_zero(const size_t size, const uint8_t flags) {
  (void)size;
  (void)flags;
  return NULL;
}

void alloc_free(const void *ptr) { (void)ptr; }

#endif  // CONFIG_ENABLED(CONFIG_ALLOC_BUDDY))
