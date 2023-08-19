// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_SCHEDULER_TASK_H
#define KERNEL_SCHEDULER_TASK_H

#include <stdint.h>

#include <kernel/config.h>

struct task_context;

enum task_state {
  TASK_RUNNING,
};

struct task {
  struct task_context *context;
  enum task_state state;
  int64_t ticks;
  int64_t priority;
  int64_t preempt;
  uint8_t padding[CONFIG_KERNEL_SCHEDULER_STACK_SIZE];
  uint8_t stack[];
};

int task_context_init(struct task *task);
void task_context_switch(struct task *next);
void task_cpu_switch(struct task_context *prev, struct task_context *next);

int task_init(void);
void task_enqueue(struct task *task);
void task_dequeue(struct task *task);
void task_tick(void);
struct task *task_pick(void);
struct task *task_get_current(void);
void task_set_current(struct task *task);

void task_schedule(void);
void task_preempt_enable(void);
void task_preempt_disable(void);
uint64_t task_get_priority(void);

#endif // !KERNEL_SCHEDULER_TASK_H