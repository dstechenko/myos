// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_SCHEDULER_TASK_H
#define KERNEL_SCHEDULER_TASK_H

#include <stdint.h>

/**
 * CPU registers context for each task.
 * Accordingly to ARM calling conventions registers x0-x18 can be overwritten
 * by the called function, so the caller must not assume that the values of
 * those registers will survive after a function call.
 */
struct task_context {
  uint64_t x19;
  uint64_t x20;
  uint64_t x21;
  uint64_t x22;
  uint64_t x23;
  uint64_t x24;
  uint64_t x25;
  uint64_t x26;
  uint64_t x27;
  uint64_t x28;
  uint64_t fp;
  uint64_t sp;
  uint64_t pc;
};

enum task_state {
  TASK_RUNNING,
};

struct task {
  struct task_context context;
  enum task_state state;
  int64_t ticks;
  int64_t priority;
  int64_t preempt;
};

void task_add(struct task *task);
void task_remove(struct task *task);
void task_schedule(void);
void task_schedule_tick(void);
void task_context_switch(struct task *next);
void task_cpu_context_switch(struct task_context *prev,
                             struct task_context *next);
void task_preempt_enable(void);
void task_preempt_disable(void);
uint64_t task_get_priority(void);

#endif // !KERNEL_SCHEDULER_TASK_H
