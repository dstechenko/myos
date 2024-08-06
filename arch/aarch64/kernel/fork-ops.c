// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/proc-regs.h>
#include <kernel/assert.h>
#include <kernel/config.h>
#include <kernel/fork.h>
#include <kernel/page.h>
#include <kernel/task.h>
#include <stddef.h>
#include <stdint.h>

#include "task-context.h"

int fork_task_context(struct task *forked, const uintptr_t pc, const uint8_t flags) {
  int err;
  struct task *current;
  struct task_context *forked_context;
  struct proc_regs *forked_regs, *current_regs;

  ASSERT(forked);

  err = task_init(forked);
  if (err) return err;

  forked_context = forked->context;
  ASSERT(forked_context);
  forked_regs = task_get_proc_regs(forked);
  ASSERT(forked_regs);

  if (flags & FORK_KERNEL) {
    ASSERT(pc);
    forked_context->x19 = pc;
  } else {
    current = task_get_current();
    ASSERT(current);
    current_regs = task_get_proc_regs(current);
    ASSERT(current_regs);
    *forked_regs = *current_regs;
    forked_regs->regs[0] = 0;
    page_copy_user_all(current, forked);
  }

  forked_context->pc = (uint64_t)entry_fork_return;
  forked_context->sp = (uint64_t)forked_regs;

  return 0;
}
