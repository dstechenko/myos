// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ARCH_AARCH64_KERNEL_PAGE_OPS_H
#define ARCH_AARCH64_KERNEL_PAGE_OPS_H

#include <kernel/page.h>
#include <kernel/task.h>
#include <stddef.h>
#include <stdint.h>

void page_init_sections(void);
void page_init_tables(void);
void page_debug(size_t limit);

uintptr_t phys_to_virt(uintptr_t paddr);
uintptr_t virt_to_phys(uintptr_t vaddr);

void map_user_page(struct task *task, struct page page);
void map_kernel_page(struct page page);

#endif  // !ARCH_AARCH64_KERNEL_PAGE_OPS_H
