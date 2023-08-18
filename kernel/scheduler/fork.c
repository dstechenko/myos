// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/scheduler/fork.h>

#include <stdint.h>

#include <kernel/memory/allocator.h>
#include <kernel/scheduler/task.h>
#include <kernel/util/assert.h>
#include <kernel/util/error.h>

#define TASK_PREEMPT_DISABLED 1

int fork(const void *func) {
  struct task *task;

  ASSERT(func);

  task_preempt_disable();
  task = zalloc(sizeof(struct task), ALLOC_NONE);
  if (!task)
    return -ENOMEM;

  task->context.x19 = (uint64_t)func;
  task->context.pc = (uint64_t)fork_return;
  task->context.sp = (uint64_t)task + PAGE_SIZE;
  task->state = TASK_RUNNING;
  task->ticks = task_get_priority();
  task->priority = task_get_priority();
  task->preempt = TASK_PREEMPT_DISABLED;

  task_add(task);
  task_preempt_enable();

  return 0;
}
