// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/scheduler/fork.h>

#include <stddef.h>
#include <stdint.h>

#include <asm/proc-regs.h>
#include <kernel/core/config.h>
#include <kernel/memory/page.h>
#include <kernel/scheduler/task.h>
#include <kernel/util/assert.h>

#include "task-context.h"

static void copy_task_memory(struct task *src, struct task *dst) {
  ASSERT(src);
  ASSERT(dst);

  /* for (int i = 0; i < src->memory.user_pages_count; i++) { */
  /*   // Copy all user pages here */
  /* } */
}

int fork_task_context(struct task *forked, const uintptr_t pc, const uint8_t flags) {
  int err;
  struct task *current;
  struct task_context *forked_context;
  struct proc_regs *forked_regs, *current_regs;

  ASSERT(forked);

  err = task_init(forked);
  if (err)
    return err;

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
    copy_task_memory(current, forked);
  }

  forked_context->pc = (uint64_t)entry_fork_return;
  forked_context->sp = (uint64_t)forked_regs;

  return 0;
}
