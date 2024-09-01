// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/memory-defs.h>
#include <asm/page-defs.h>

#include <kernel/assert.h>
#include <kernel/config.h>
#include <kernel/ptrs.h>
#include <kernel/types.h>

#define PAGE_MEMORY_START PHYSICAL_MEMORY_START
#define PAGE_MEMORY_SIZE PHYSICAL_MEMORY_SIZE
#define PAGE_COUNT (PAGE_MEMORY_SIZE / PAGE_SIZE)
#define PAGE_FROM_INDEX(index) ((uintptr_t)(PAGE_MEMORY_START + index * PAGE_SIZE))
#define PAGE_TO_INDEX(page) ((page - PAGE_MEMORY_START) / PAGE_SIZE)

struct page_metadata {
  bool used;
};

static struct page_metadata pages[PAGE_COUNT];

uintptr_t page_get(size_t order) {
  size_t i;

  for (i = 0; i < sizeof(pages); i++)
    if (!pages[i].used) {
      pages[i].used = true;
      return PAGE_FROM_INDEX(i);
    }

  return PTR_TO_ADR(NULL);
}

void page_put(const uintptr_t page) {
  if (page) pages[PAGE_TO_INDEX(page)].used = false;
}

void page_reserve_range(uintptr_t begin, const uintptr_t end) {
  ASSERT(begin < end);
  ASSERT(begin % PAGE_SIZE == 0);
  while (begin < end) {
    pages[PAGE_TO_INDEX(begin)].used = true;
    begin += PAGE_SIZE;
  }
}
