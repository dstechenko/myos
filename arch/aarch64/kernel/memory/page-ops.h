// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ARCH_AARCH64_KERNEL_MEMORY_PAGE_OPS_H
#define ARCH_AARCH64_KERNEL_MEMORY_PAGE_OPS_H

#include <stdint.h>

#include <kernel/memory/page.h>
#include <kernel/scheduler/task.h>

void debug_pages(void);
void map_user_page(struct task *task, struct page page);
uintptr_t map_user_table();
void map_user_table_entry(uintptr_t *entry, struct page page);

#endif // !ARCH_AARCH64_KERNEL_MEMORY_PAGE_OPS_H
