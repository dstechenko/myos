// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/cpu.h>
#include <asm/proc-regs.h>

#include <kernel/assert.h>
#include <kernel/config.h>
#include <kernel/error.h>
#include <kernel/memory-ops.h>
#include <kernel/memory.h>
#include <kernel/ptrs.h>
#include <kernel/task.h>

#include "page-context.h"
#include "task-context.h"

// TODO(dstechenko): move out of here
#define PSR_MODE_EL0t 0x00000000
#define PSR_MODE_EL1t 0x00000004
#define PSR_MODE_EL1h 0x00000005
#define PSR_MODE_EL2t 0x00000008
#define PSR_MODE_EL2h 0x00000009
#define PSR_MODE_EL3t 0x0000000C
#define PSR_MODE_EL3h 0x0000000D

#define TASK_STACK_SIZE CONFIG_SCHEDULER_STACK_SIZE

int task_init(struct task *task) {
  ASSERT(task);

  ASSERT(sizeof(struct task_context));
  task->context = memory_zalloc(sizeof(struct task_context), PF_KERNEL);
  if (!task->context) return -ENOMEM;

  ASSERT(sizeof(struct page_context));
  task->memory.context = memory_zalloc(sizeof(struct page_context), PF_KERNEL);
  if (!task->memory.context) return -ENOMEM;

  ASSERT(TASK_STACK_SIZE);
  task->stack = memory_zalloc(TASK_STACK_SIZE, PF_KERNEL);
  if (!task->stack) return -ENOMEM;

  return 0;
}

struct proc_regs *task_get_proc_regs(struct task *task) {
  uintptr_t stack;

  ASSERT(task);
  ASSERT(task->stack);
  stack = (uintptr_t)task->stack + TASK_STACK_SIZE;

  return (struct proc_regs *)(stack - sizeof(struct proc_regs));
}

int task_move_to_user(const uintptr_t pc, const uintptr_t text, const size_t size) {
  struct task *current;
  struct proc_regs *current_regs;
  uintptr_t page;

  // TOOD(dstechenko): check pc within text/size
  ASSERT(pc);
  current = task_get_current();
  ASSERT(current);
  ASSERT(current->memory.context);
  current_regs = task_get_proc_regs(current);
  ASSERT(current_regs);

  // TODO(dstechenko): make these pages data
  page = page_get_user(current, 1 * PAGE_SIZE, /* order = */ 0);
  current->user_stack = (void *)PAGE_SIZE;
  page_clear_cache(page);

  // TODO(dstechenko): make these pages executable
  page = page_get_user(current, 2 * PAGE_SIZE, /* order = */ 0);
  memory_copy(ADR_TO_PTR(page), ADR_TO_PTR(text), size);
  page_clear_cache(page);

  current_regs->sp = (uint64_t)current->user_stack + TASK_STACK_SIZE;
  current_regs->pc = (uint64_t)(2 * PAGE_SIZE);
  current_regs->ps = (uint64_t)PSR_MODE_EL0t;

  cpu_set_user_pt(current->memory.context->pgd);

  return 0;
}
