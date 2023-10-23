// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ARCH_AARCH64_KERNEL_MEMORY_PAGE_OPS_H
#define ARCH_AARCH64_KERNEL_MEMORY_PAGE_OPS_H

#include <stddef.h>
#include <stdint.h>

#include <kernel/memory/page.h>
#include <kernel/scheduler/task.h>

void page_init_sections(void);
void page_init_tables(void);
void page_debug(size_t limit);

void map_user_page(struct task *task, struct page page);
void map_kernel_page(struct page page);

#endif // !ARCH_AARCH64_KERNEL_MEMORY_PAGE_OPS_H
