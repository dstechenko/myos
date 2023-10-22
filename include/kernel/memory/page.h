// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_MEMORY_PAGE_H
#define KERNEL_MEMORY_PAGE_H

#include <stdint.h>
#include <stddef.h>

#include <asm/page-defs.h>

struct task;

struct page {
  uintptr_t vaddr;
  uintptr_t paddr;
};

uintptr_t get_page(void);
uintptr_t get_kernel_page(void);
uintptr_t get_user_page(struct task *task, uintptr_t vaddr);
void put_page(uintptr_t page);
int copy_user_pages(const struct task *src, struct task *dst);

void page_init(void);
void page_debug(size_t limit);
void map_user_page(struct task *task, struct page page);

#endif // !KERNEL_MEMORY_PAGE_H
