// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_SCHEDULER_TASK_H
#define KERNEL_SCHEDULER_TASK_H

#include <stddef.h>
#include <stdint.h>

#include <kernel/core/config.h>
#include <kernel/memory/page.h>

struct proc_regs;
struct task_context;
struct page_context;

enum task_state {
  TASK_RUNNING,
  TASK_ZOMBIE,
};

#define TASK_MAX_PROCESS_PAGES 16

struct task_memory {
  struct page user_pages[TASK_MAX_PROCESS_PAGES];
  size_t user_pages_count;
  struct page kernel_pages[TASK_MAX_PROCESS_PAGES];
  size_t kernel_pages_count;
  struct page_context *context;
};

struct task {
  uint64_t id;
  struct task_context *context;
  struct task_memory memory;
  enum task_state state;
  uint8_t flags;
  int64_t priority;
  int64_t ticks;
  int64_t preempt;
  void *stack;
  void *user_stack;
};

int task_init(struct task *task);
void task_cpu_switch(struct task_context *prev, struct task_context *next);
struct proc_regs *task_get_proc_regs(struct task *task);

int task_main_init(void);
int task_enqueue(struct task *task);
void task_dequeue(struct task *task);
void task_tick(void);
struct task *task_pick(void);
struct task *task_get_current(void);
void task_set_current(struct task *task);

void task_schedule(void);
void task_context_switch(struct task *next);
void task_preempt_enable(void);
void task_preempt_disable(void);
uint64_t task_get_priority(void);
int task_move_to_user(uintptr_t pc, uintptr_t text, size_t size);
int task_copy_vmem_into(struct task *task);
void task_exit(void);

#endif // !KERNEL_SCHEDULER_TASK_H
