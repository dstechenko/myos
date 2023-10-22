// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/memory/page.h>

#include <stddef.h>

#include <asm/memory-defs.h>
#include <asm/page-defs.h>

#include <kernel/core/config.h>
#include <kernel/core/error.h>
#include <kernel/memory/ops.h>
#include <kernel/scheduler/task.h>
#include <kernel/util/assert.h>
#include <kernel/util/ptrs.h>
#include <uapi/bool.h>

// TODO(dstechenko): move to smaller pages
// TODO(dstechenko): mark kernel/boot pages as used
// TODO(dstechenko): move to faster traversal
// TODO(dstechenko): do not map the first page into virtual for user/kernel
// TODO(dstechenko): add handle mem abort to map pages

#define STATIC_PAGES 30
#define STATIC_PAGE_SIZE SECTION_SIZE
#define STATIC_MEMORY_MAX PHYSICAL_DEVICE_MEMORY_START
#define STATIC_MEMORY_SIZE (STATIC_PAGES * STATIC_PAGE_SIZE)
#define STATIC_MEMORY_MIN (STATIC_MEMORY_MAX - STATIC_MEMORY_SIZE)

#define INDEX_TO_ADDRESS(page) ((uintptr_t)(STATIC_MEMORY_MIN + page * STATIC_PAGE_SIZE))
#define ADDRESS_TO_INDEX(addr) ((addr - STATIC_MEMORY_MIN) / STATIC_PAGE_SIZE)

static bool pages[STATIC_PAGES];

// TODO(dstechenko): add proper zero pages
uintptr_t get_page(void) {
  size_t i;

  for (i = 0; i < sizeof(pages); i++)
    if (!pages[i]) {
      pages[i] = true;
      return INDEX_TO_ADDRESS(i);
    }

  return PTR_TO_ADR(NULL);
}

uintptr_t get_kernel_page(void) {
  uintptr_t page = get_page();

  if (page)
    page += VIRTUAL_MEMORY_START;

  return page;
}

uintptr_t get_user_page(struct task *task, uintptr_t vaddr) {
  uintptr_t page;

  ASSERT(task);

  page = get_page();
  if (page) {
    map_user_page(task, (struct page){.vaddr = vaddr, .paddr = page});
    page += VIRTUAL_MEMORY_START;
  }

  return page;
}

void put_page(const uintptr_t page) {
  if (page)
    pages[ADDRESS_TO_INDEX(page)] = false;
}

int copy_user_pages(const struct task *src, struct task *dst) {
  size_t src_count;
  const struct page *src_pages;

  ASSERT(src);
  ASSERT(dst);
  src_count = src->memory.user_pages_count;
  src_pages = src->memory.user_pages;

  for (size_t i = 0; i < src_count; i++) {
    uintptr_t page = get_user_page(dst, src_pages[i].vaddr);
    if (!page)
      return -ENOMEM;
    memcpy(ADR_TO_PTR(page), ADR_TO_PTR(src_pages[i].vaddr), PAGE_SIZE - 1);
  }

  return 0;
}
