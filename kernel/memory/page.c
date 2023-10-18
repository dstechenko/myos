// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/memory/page.h>

#include <stddef.h>

#include <asm/memory-defs.h>
#include <asm/page-defs.h>
#include <kernel/memory/ops.h>
#include <kernel/util/bool.h>
#include <kernel/core/config.h>

#define STATIC_PAGES       50
#define STATIC_PAGE_SIZE   SECTION_SIZE
#define STATIC_MEMORY_MAX  PHYSICAL_DEVICE_MEMORY_START
#define STATIC_MEMORY_SIZE (STATIC_PAGES * STATIC_PAGE_SIZE)
#define STATIC_MEMORY_MIN  (STATIC_MEMORY_MAX - STATIC_MEMORY_SIZE)

#define INDEX_TO_ADDRESS(page) ((uintptr_t)(STATIC_MEMORY_MIN + page * STATIC_PAGE_SIZE))
#define ADDRESS_TO_INDEX(addr) ((addr - STATIC_MEMORY_MIN) / STATIC_PAGE_SIZE)

static bool pages[STATIC_PAGES];

uintptr_t get_free_page() {
  size_t i;

  for (i = 0; i < sizeof(pages); i++)
    if (!pages[i]) {
      pages[i] = true;
      return INDEX_TO_ADDRESS(i);
    }

  return (uintptr_t)NULL;
}

void free_page(const uintptr_t page) {
  if (page)
    pages[ADDRESS_TO_INDEX(page)] = false;
}
