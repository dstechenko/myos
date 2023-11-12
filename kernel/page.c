// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/page.h>

#include <stddef.h>

#include <asm/memory-defs.h>
#include <asm/page-defs.h>

#include <kernel/assert.h>
#include <kernel/config.h>
#include <kernel/error.h>
#include <kernel/memory-ops.h>
#include <kernel/ptrs.h>
#include <kernel/task.h>
#include <uapi/bool.h>

// TODO(dstechenko): move to smaller pages
// TODO(dstechenko): mark kernel/boot pages as used
// TODO(dstechenko): move to faster traversal
// TODO(dstechenko): do not map the first page into virtual for user/kernel
// TODO(dstechenko): add handle mem abort to map pages
// TODO(dstechenko): unmap pages

#define PAGE_MEMORY_START PHYSICAL_MEMORY_START
#define PAGE_MEMORY_SIZE PHYSICAL_MEMORY_SIZE
#define PAGE_COUNT (PAGE_MEMORY_SIZE / PAGE_SIZE)
#define PAGE_FROM_INDEX(index) ((uintptr_t)(PAGE_MEMORY_START + index * PAGE_SIZE))
#define PAGE_TO_INDEX(page) ((page - PAGE_MEMORY_START) / PAGE_SIZE)
static struct page_metadata pages[PAGE_COUNT];

void page_init(void) {
  page_init_sections();
  page_init_tables();
}

void page_reserve_range(uintptr_t begin, const uintptr_t end) {
  // TODO(dstechenko): assert it is page aligned
  ASSERT(begin < end);
  while (begin < end) {
    pages[PAGE_TO_INDEX(begin)].used = true;
    begin += PAGE_SIZE;
  }
}

// TODO(dstechenko): add proper zero pages
uintptr_t get_page(void) {
  size_t i;

  for (i = 0; i < sizeof(pages); i++)
    if (!pages[i].used) {
      pages[i].used = true;
      return PAGE_FROM_INDEX(i);
    }

  return PTR_TO_ADR(NULL);
}

uintptr_t get_kernel_page(void) {
  uintptr_t paddr = get_page();

  return paddr ? phys_to_virt(paddr) : paddr;
}

// TODO(dstecheko): use pages, use last available vaddr for task?
uintptr_t get_user_page(struct task *task, const uintptr_t vaddr) {
  uintptr_t paddr;

  ASSERT(task);

  paddr = get_page();
  if (paddr)
    map_user_page(task, (struct page){.vaddr = vaddr, .paddr = paddr});

  return paddr ? phys_to_virt(paddr) : paddr;
}

void put_page(const uintptr_t page) {
  if (page)
    pages[PAGE_TO_INDEX(page)].used = false;
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
