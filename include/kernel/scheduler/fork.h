// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_SCHEDULER_FORK_H
#define KERNEL_SCHEDULER_FORK_H

#include <stdint.h>

#include <kernel/scheduler/task.h>
#include <kernel/util/bits.h>

#define FORK_KERNEL BIT(0)

int fork_task(const void *pc, uint8_t flags);
int fork_task_context(struct task *task, const void *pc, uint8_t flags);
void entry_fork_return(void);

#endif // !KERNEL_SCHEDULER_FORK_H
