// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/scheduler/fork.h>

#include <kernel/core/error.h>
#include <kernel/memory/allocator.h>
#include <kernel/scheduler/task.h>

#define TASK_PREEMPT_DISABLED 1

int fork_task(const uintptr_t pc, const uintptr_t sp, const uint8_t flags) {
  int err;
  struct task *task;

  task_preempt_disable();
  task = zalloc(sizeof(struct task), ALLOC_KERNEL);
  if (!task)
    return -ENOMEM;

  err = fork_task_context(task, pc, sp, flags);
  if (err)
    return err;

  task->state = TASK_RUNNING;
  task->flags = flags;
  task->priority = task_get_priority();
  task->ticks = task->priority;
  task->preempt = TASK_PREEMPT_DISABLED;

  // TODO: handle inability to add tasks
  task_enqueue(task);
  task_preempt_enable();

  // TODO: make sure task ids always fit into ints
  return (int)task->id;
}
