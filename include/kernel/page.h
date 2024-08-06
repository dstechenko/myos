// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_PAGE_H
#define KERNEL_PAGE_H

#include <asm/page-defs.h>

#include <kernel/types.h>

struct task;

struct page {
  uintptr_t vaddr;
  uintptr_t paddr;
};

struct page_metadata {
  bool used;
};

void page_init(void);
void page_reserve_range(uintptr_t begin, uintptr_t end);
uintptr_t page_get(void);
uintptr_t page_get_kernel(void);
uintptr_t page_get_user(struct task *task, uintptr_t vaddr);
void page_put(uintptr_t page);
int page_copy_user_all(const struct task *src, struct task *dst);
void page_clear_cache(uintptr_t page);

uintptr_t phys_to_virt(uintptr_t paddr);
uintptr_t virt_to_phys(uintptr_t vaddr);
struct page phys_to_page(uintptr_t paddr);

void page_init_sections(void);
void page_init_tables(void);
void page_debug(size_t limit);
void page_map_user(struct task *task, struct page page);
void page_map_kernel(struct page page);

#endif // !KERNEL_PAGE_H
