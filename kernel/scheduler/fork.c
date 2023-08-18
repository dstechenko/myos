// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/scheduler/fork.h>

#include <kernel/memory/allocator.h>
#include <kernel/scheduler/task.h>
#include <kernel/util/assert.h>
#include <kernel/util/error.h>

#define TASK_PREEMPT_DISABLED 1

int fork(const void *func) {
  int err;
  struct task *task;

  ASSERT(func);

  task_preempt_disable();
  task = zalloc(sizeof(struct task), ALLOC_NONE);
  if (!task)
    return -ENOMEM;

  err = fork_task_context(task, func);
  if (err)
    return err;

  task->state = TASK_RUNNING;
  task->ticks = task_get_priority();
  task->priority = task_get_priority();
  task->preempt = TASK_PREEMPT_DISABLED;

  task_enqueue(task);
  task_preempt_enable();

  return 0;
}
