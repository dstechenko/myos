// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/barrier.h>
#include <asm/cache.h>
#include <asm/memory-defs.h>
#include <asm/page-defs.h>

#include <kernel/assert.h>
#include <kernel/config.h>
#include <kernel/error.h>
#include <kernel/memory-ops.h>
#include <kernel/page.h>
#include <kernel/ptrs.h>
#include <kernel/task.h>
#include <kernel/types.h>

// TODO(dstechenko): do faster traversal
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
  ASSERT(begin < end);
  ASSERT(begin % PAGE_SIZE == 0);
  while (begin < end) {
    pages[PAGE_TO_INDEX(begin)].used = true;
    begin += PAGE_SIZE;
  }
}

uintptr_t page_get(void) {
  size_t i;

  // TODO(dstechenko): add proper zero pages
  for (i = 0; i < sizeof(pages); i++)
    if (!pages[i].used) {
      pages[i].used = true;
      return PAGE_FROM_INDEX(i);
    }

  return PTR_TO_ADR(NULL);
}

uintptr_t page_get_kernel(void) {
  uintptr_t paddr = page_get();

  return paddr ? phys_to_virt(paddr) : paddr;
}

void page_clear_cache(uintptr_t va) {
  for (uintptr_t ptr = va; ptr < va + PAGE_SIZE; ptr += CONFIG_CACHE_LINE) {
    cache_inv_data(ptr);
    cache_inv_inst(ptr);
  }
  barrier_data_sync();
  barrier_inst_sync();
}

// TODO(dstecheko): use pages, use last available vaddr for task?
uintptr_t page_get_user(struct task *task, const uintptr_t vaddr) {
  uintptr_t paddr, page;

  ASSERT(task);

  paddr = page_get();
  if (paddr) page_map_user(task, (struct page){.vaddr = vaddr, .paddr = paddr});

  page = paddr ? phys_to_virt(paddr) : paddr;
  if (page) page_clear_cache(page);

  return page;
}

void page_put(const uintptr_t page) {
  if (page) pages[PAGE_TO_INDEX(page)].used = false;
}

int page_copy_user_all(const struct task *src, struct task *dst) {
  size_t src_count;
  const struct page *src_pages;

  ASSERT(src);
  ASSERT(dst);
  src_count = src->memory.user_pages_count;
  src_pages = src->memory.user_pages;

  for (size_t i = 0; i < src_count; i++) {
    uintptr_t page = page_get_user(dst, src_pages[i].vaddr);
    if (!page) return -ENOMEM;
    memcpy(ADR_TO_PTR(page), ADR_TO_PTR(src_pages[i].vaddr), PAGE_SIZE - 1);
  }

  return 0;
}
