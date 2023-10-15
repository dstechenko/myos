// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_MEMORY_PAGE_H
#define KERNEL_MEMORY_PAGE_H

#include <stdint.h>

#include <asm/page-defs.h>

struct task;

struct page {
  uintptr_t vaddr;
  uintptr_t paddr;
};

uintptr_t get_free_page(void);
uintptr_t get_free_page_zero(void);
uintptr_t get_free_page_kernel(void);
uintptr_t get_free_page_user(struct task *task, uintptr_t vaddr);

void free_page(uintptr_t page);

void debug_pages(void);

#endif // !KERNEL_MEMORY_PAGE_H
