// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/barrier.h>
#include <asm/cache.h>

#include <kernel/assert.h>
#include <kernel/config.h>
#include <kernel/error.h>
#include <kernel/memory-ops.h>
#include <kernel/page.h>
#include <kernel/ptrs.h>
#include <kernel/task.h>
#include <kernel/types.h>

void page_init(void) {
  page_init_sections();
  page_init_tables();
}

uintptr_t page_get_kernel(const size_t order) {
  uintptr_t paddr = page_get(order);
  return paddr ? phys_to_virt(paddr) : paddr;
}

// TODO(dstecheko): track available pages for a process instead of arg
uintptr_t page_get_user(struct task *task, const uintptr_t vaddr, size_t order) {
  uintptr_t paddr, page;

  ASSERT(task);
  paddr = page_get(order);
  if (paddr == NULL) return NULL;

  page_map_user(task, (struct page){.vaddr = vaddr, .paddr = paddr});
  page = phys_to_virt(paddr);
  page_clear_cache(page);

  return page;
}

int page_copy_user_all(const struct task *src, struct task *dst) {
  size_t src_count;
  const struct page *src_pages;

  ASSERT(src);
  ASSERT(dst);
  src_count = src->memory.user_pages_count;
  src_pages = src->memory.user_pages;

  for (size_t i = 0; i < src_count; i++) {
    uintptr_t page = page_get_user(dst, src_pages[i].vaddr, /* order = */ 0);
    if (!page) return -ENOMEM;
    memory_copy(ADR_TO_PTR(page), ADR_TO_PTR(src_pages[i].vaddr), PAGE_SIZE - 1);
  }

  return 0;
}

void page_clear_cache(const uintptr_t vaddr) {
  for (uintptr_t ptr = vaddr; ptr < vaddr + PAGE_SIZE; ptr += CONFIG_CACHE_LINE) {
    cache_inv_data(ptr);
    cache_inv_inst(ptr);
  }
  barrier_data_sync();
  barrier_inst_sync();
}
