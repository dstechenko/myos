// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/scheduler/task.h>

#include <asm/proc-regs.h>
#include <asm/registers.h>

#include <kernel/core/config.h>
#include <kernel/core/error.h>
#include <kernel/memory/allocator.h>
#include <kernel/util/assert.h>
#include <kernel/util/ptrs.h>

#include "../memory/page-context.h"
#include "task-context.h"

// TODO: move out of here
#define PSR_MODE_EL0t 0x00000000
#define PSR_MODE_EL1t 0x00000004
#define PSR_MODE_EL1h 0x00000005
#define PSR_MODE_EL2t 0x00000008
#define PSR_MODE_EL2h 0x00000009
#define PSR_MODE_EL3t 0x0000000C
#define PSR_MODE_EL3h 0x0000000D

#define TASK_STACK_SIZE CONFIG_KERNEL_SCHEDULER_STACK_SIZE

int task_init(struct task *task) {
  ASSERT(task);

  task->context = zalloc(sizeof(struct task_context), ALLOC_KERNEL);
  if (!task->context)
    return -ENOMEM;

  task->memory.context = zalloc(sizeof(struct page_context), ALLOC_KERNEL);
  if (!task->memory.context)
    return -ENOMEM;

  task->stack = zalloc(TASK_STACK_SIZE, ALLOC_KERNEL);
  if (!task->stack)
    return -ENOMEM;

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
  uintptr_t text_page;

  ASSERT(pc);
  current = task_get_current();
  ASSERT(current);
  current_regs = task_get_proc_regs(current);
  ASSERT(current_regs);

  current->user_stack = ADR_TO_PTR(get_user_page(current, 0));
  if (!current->user_stack)
    return -ENOMEM;

  current_regs->sp = (uint64_t)current->user_stack + TASK_STACK_SIZE;
  current_regs->pc = (uint64_t)pc;
  current_regs->ps = (uint64_t)PSR_MODE_EL0t;

  text_page = get_user_page(current, SECTION_SIZE);
  memcpy(text_page, text, size);

  ASSERT(current->memory.context);
  registers_set_user_page_table(current->memory.context->pgd);

  return 0;
}
