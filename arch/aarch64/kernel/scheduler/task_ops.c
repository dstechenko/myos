// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/scheduler/task.h>

#include <kernel/core/error.h>
#include <kernel/memory/allocator.h>
#include <kernel/util/assert.h>

#include "proc_regs.h"
#include "task_context.h"

int task_context_init(struct task *task) {
  ASSERT(task);
  task->context = zalloc(sizeof(struct task_context), ALLOC_NONE);
  if (!task->context)
    return -ENOMEM;
  return 0;
}

struct proc_regs *task_get_proc_regs(struct task *task) {
  return (struct proc_regs *)(task->stack - sizeof(struct proc_regs));
}
