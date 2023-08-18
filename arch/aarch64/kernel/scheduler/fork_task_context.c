// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/scheduler/fork.h>

#include <stdint.h>

#include <kernel/util/assert.h>

#include "task_context.h"

int fork_task_context(struct task *task, const void *func) {
  int err;

  ASSERT(task);
  ASSERT(func);

  err = task_context_init(task);
  if (err)
    return err;

  task->context->x19 = (uint64_t)func;
  task->context->pc = (uint64_t)fork_return;
  task->context->sp = (uint64_t)task->stack;

  return 0;
}
