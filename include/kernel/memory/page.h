// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_MEMORY_PAGE_H
#define KERNEL_MEMORY_PAGE_H

#include <stdint.h>

#include <asm/page-defs.h>
#include <kernel/util/bits.h>

struct task;

struct page {
  uintptr_t vaddr;
  uintptr_t paddr;
};

uintptr_t get_free_page();
uintptr_t get_free_page_kernel();
uintptr_t get_free_page_user(struct task *task, uintptr_t vaddr);
void free_page(uintptr_t page);

void map_table_entry();
void map_table();
void map_page();

#endif // !KERNEL_MEMORY_PAGE_H
