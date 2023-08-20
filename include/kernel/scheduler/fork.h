// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_SCHEDULER_FORK_H
#define KERNEL_SCHEDULER_FORK_H

#include <kernel/scheduler/task.h>

int fork_task(const void *pc);
int fork_task_context(struct task *task, const void *pc);

#endif // !KERNEL_SCHEDULER_FORK_H
