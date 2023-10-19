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

uintptr_t get_page(void);
uintptr_t get_kernel_page(void);
uintptr_t get_user_page(struct task *task, uintptr_t vaddr);
void free_page(uintptr_t page);

void map_user_page();
uintptr_t map_user_table();
void map_user_table_entry();

void debug_pages(void);

#endif // !KERNEL_MEMORY_PAGE_H
