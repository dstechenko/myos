// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/allocator.h>
#include <kernel/assert.h>
#include <kernel/error.h>
#include <kernel/fork.h>
#include <kernel/task.h>

#define TASK_PREEMPT_DISABLED 1

int fork_task(const uintptr_t pc, const uint8_t flags) {
  int err;
  struct task *task;

  task_preempt_disable();
  ASSERT(sizeof(struct task));
  task = zalloc(sizeof(struct task), ALLOC_KERNEL);
  if (!task) return -ENOMEM;

  err = fork_task_context(task, pc, flags);
  if (err) return err;

  task->state = TASK_RUNNING;
  task->flags = flags;
  task->priority = task_get_priority();
  task->ticks = task->priority;
  task->preempt = TASK_PREEMPT_DISABLED;

  // TODO(dstechenko): handle inability to add tasks
  task_enqueue(task);
  task_preempt_enable();

  // TODO(dstechenko): make sure task ids always fit into ints
  return (int)task->id;
}
