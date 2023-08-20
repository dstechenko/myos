// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/scheduler/fork.h>

#include <stddef.h>
#include <stdint.h>

#include <kernel/memory/ops.h>
#include <kernel/scheduler/task.h>
#include <kernel/util/assert.h>

#include "proc_regs.h"
#include "task_context.h"

int fork_task_context(struct task *forked, const void *pc,
                      const uint8_t flags) {
  int err;
  struct task *current;
  struct task_context *forked_context;
  struct proc_regs *forked_regs, *current_regs;

  ASSERT(forked);
  ASSERT(pc);

  err = task_context_init(forked);
  if (err)
    return err;

  forked_context = forked->context;
  ASSERT(forked_context);
  forked_regs = task_get_proc_regs(forked);
  ASSERT(forked_regs);

  if (flags & FORK_KERNEL) {
    forked_context->x19 = (uint64_t)pc;
  } else {
    current = task_get_current();
    ASSERT(current);
    current_regs = task_get_proc_regs(current);
    ASSERT(current_regs);
    *forked_regs = *current_regs;
    forked_regs->regs[0] = 0;
    forked_regs->sp = (uint64_t)NULL;
  }

  forked_context->pc = (uint64_t)entry_fork_return;
  forked_context->sp = (uint64_t)forked_regs;

  return 0;
}
