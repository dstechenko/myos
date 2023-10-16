// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/memory/page.h>

#include <stddef.h>

#include <asm/memory-defs.h>
#include <asm/page-defs.h>
#include <kernel/memory/ops.h>
#include <kernel/util/bool.h>

#define STATIC_MEMORY_MIN (30 * SECTION_SIZE)
#define STATIC_MEMORY_HIGH 0x3F000000

#define STATIC_MEMORY (STATIC_MEMORY_HIGH - STATIC_MEMORY_MIN)
#define STATIC_PAGES (STATIC_MEMORY / PAGE_SIZE)

#define INDEX_TO_MEMORY(page) ((uintptr_t)(STATIC_MEMORY_MIN + page * PAGE_SIZE))
#define MEMORY_TO_INDEX(addr) ((addr - STATIC_MEMORY_MIN) / PAGE_SIZE)

static bool pages[STATIC_PAGES];

static uintptr_t get_virtual_address(uintptr_t paddr) { return VIRTUAL_MEMORY_START + paddr; }

uintptr_t get_free_page() {
  size_t i;

  for (i = 0; i < sizeof(pages); i++)
    if (!pages[i]) {
      pages[i] = true;
      return INDEX_TO_MEMORY(i);
    }

  return (uintptr_t)NULL;
}

uintptr_t get_free_page_zero() {
  uintptr_t page = get_free_page();

  if (page)
    memzero((void *)get_virtual_address(page), PAGE_SIZE);

  return page;
}

uintptr_t get_free_page_kernel() { return (uintptr_t)NULL; }

uintptr_t get_free_page_user(struct task *task, uintptr_t vaddr) {
  (void)task;
  (void)vaddr;
  return (uintptr_t)NULL;
}

void free_page(const uintptr_t page) {
  if (page)
    pages[MEMORY_TO_INDEX(page)] = false;
}
