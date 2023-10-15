// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ARCH_AARCH64_KERNEL_MEMORY_PAGE_OPS_H
#define ARCH_AARCH64_KERNEL_MEMORY_PAGE_OPS_H

#include <stdint.h>

void map_table_entry();
void map_table();
void map_page();

void set_page_global_directory(uintptr_t pgd);
uintptr_t get_page_global_directory(void);
void print_page_global_directory(uintptr_t pgd);

void debug_pages(void);

#endif // !ARCH_AARCH64_KERNEL_MEMORY_PAGE_OPS_H
