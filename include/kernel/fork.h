// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_FORK_H
#define KERNEL_FORK_H

#include <kernel/task.h>
#include <kernel/bits.h>
#include <kernel/types.h>

#define FORK_KERNEL BIT(0)
#define FORK_USER BIT(1)

void entry_fork_return(void);

int fork_task(uintptr_t pc, uint8_t flags);
int fork_task_context(struct task *task, uintptr_t pc, uint8_t flags);

#endif // !KERNEL_FORK_H
