// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/scheduler/task.h>

#include <kernel/memory/allocator.h>
#include <kernel/util/assert.h>
#include <kernel/core/error.h>

#include "task_context.h"

int task_context_init(struct task *task) {
  struct task_context *context;

  ASSERT(task);

  context = zalloc(sizeof(struct task_context), ALLOC_NONE);
  if (!context)
    return -ENOMEM;

  task->context = context;

  return 0;
}
