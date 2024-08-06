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
uintptr_t get_page(void);
uintptr_t get_kernel_page(void);
uintptr_t get_user_page(struct task *task, uintptr_t vaddr);
void put_page(uintptr_t page);
int copy_user_pages(const struct task *src, struct task *dst);
void clear_page_cache(uintptr_t page);

uintptr_t phys_to_virt(uintptr_t paddr);
uintptr_t virt_to_phys(uintptr_t vaddr);
struct page phys_to_page(uintptr_t paddr);

void page_init_sections(void);
void page_init_tables(void);
void page_debug(size_t limit);
void map_user_page(struct task *task, struct page page);
void map_kernel_page(struct page page);

#endif // !KERNEL_PAGE_H
