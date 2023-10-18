// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/scheduler/task.h>

#include <asm/proc-regs.h>
#include <kernel/core/config.h>
#include <kernel/core/error.h>
#include <kernel/memory/allocator.h>
#include <kernel/util/assert.h>

// TODO: remove (debug)
#include <kernel/logging/log.h>

#include "task-context.h"

// TODO: move out of here
#define PSR_MODE_EL0t 0x00000000
#define PSR_MODE_EL1t 0x00000004
#define PSR_MODE_EL1h 0x00000005
#define PSR_MODE_EL2t 0x00000008
#define PSR_MODE_EL2h 0x00000009
#define PSR_MODE_EL3t 0x0000000C
#define PSR_MODE_EL3h 0x0000000D

int task_init(struct task *task) {
  ASSERT(task);

  task->context = zalloc(sizeof(struct task_context), ALLOC_KERNEL);
  if (!task->context)
    return -ENOMEM;

  task->stack = zalloc(CONFIG_KERNEL_SCHEDULER_STACK_SIZE, ALLOC_KERNEL);
  if (!task->stack)
    return -ENOMEM;

  return 0;
}

struct proc_regs *task_get_proc_regs(struct task *task) {
  uintptr_t stack;

  ASSERT(task);
  ASSERT(task->stack);
  stack = (uintptr_t)task->stack + CONFIG_KERNEL_SCHEDULER_STACK_SIZE;

  return (struct proc_regs *)(stack - sizeof(struct proc_regs));
}

int task_move_to_user(const uintptr_t pc) {
  struct task *current;
  struct proc_regs *current_regs;

  ASSERT(pc);
  current = task_get_current();
  ASSERT(current);
  current_regs = task_get_proc_regs(current);
  ASSERT(current_regs);

  current->user_stack = zalloc(CONFIG_KERNEL_SCHEDULER_STACK_SIZE, ALLOC_USER);
  if (!current->user_stack)
    return -ENOMEM;

  // TODO: remove (debug)
  LOG_INFO("user stack addr %lx", (current->user_stack + CONFIG_KERNEL_SCHEDULER_STACK_SIZE));
  uint64_t *ptr = (uint64_t *)(current->user_stack + CONFIG_KERNEL_SCHEDULER_STACK_SIZE);
  ptr[2] = 42;
  LOG_INFO("user stack read %ld", ptr[2]);

  current_regs->sp = (uint64_t)current->user_stack + CONFIG_KERNEL_SCHEDULER_STACK_SIZE;
  current_regs->pc = (uint64_t)pc;
  current_regs->ps = (uint64_t)PSR_MODE_EL0t;

  return 0;
}
