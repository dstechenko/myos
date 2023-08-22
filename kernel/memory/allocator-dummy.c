// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/memory/allocator.h>

#include <stdint.h>

#include <asm/page.h>
#include <kernel/core/config.h>
#include <kernel/memory/ops.h>
#include <kernel/util/assert.h>
#include <kernel/util/bool.h>

#define STATIC_MEMORY_MIN (100 * PAGE_SIZE)
#define STATIC_MEMORY_HIGH 0x3F000000

#define STATIC_MEMORY (STATIC_MEMORY_HIGH - STATIC_MEMORY_MIN)
#define STATIC_PAGES (STATIC_MEMORY / PAGE_SIZE)

#define PAGE_TO_MEMORY(page) ((void *)(STATIC_MEMORY_MIN + page * PAGE_SIZE))
#define MEMORY_TO_PAGE(addr) (((uintptr_t)addr - STATIC_MEMORY_MIN) / PAGE_SIZE)

static bool memory_map[STATIC_PAGES] = {0};

void *alloc(const size_t size, const uint8_t flags) {
  size_t i;

  (void)flags;
  (void)size;

  ASSERT(size);
  ASSERT(size <= PAGE_SIZE);

  for (i = 0; i < sizeof(memory_map); i++)
    if (!memory_map[i]) {
      memory_map[i] = true;
      return PAGE_TO_MEMORY(i);
    }

  return NULL;
}

void *zalloc(const size_t size, const uint8_t flags) {
  uint8_t *obj = (uint8_t *)alloc(size, flags);

  if (obj)
    memzero(obj, size);

  return obj;
}

void free(const void *obj) {
  if (obj)
    memory_map[MEMORY_TO_PAGE(obj)] = false;
}
