// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/scheduler/task.h>

#include <kernel/logging/log.h>
#include <kernel/memory/allocator.h>
#include <kernel/util/assert.h>

static void task_schedule_loop(void) {
  task_preempt_disable();
  task_context_switch(task_pick());
  task_preempt_enable();
}

static void task_clean_up(struct task *task) {
  ASSERT(task);

  if (task->state != TASK_ZOMBIE)
    return;

  if (task->context) {
    free(task->context);
    task->context = NULL;
  }

  if (task->stack) {
    free(task->stack);
    task->stack = NULL;
  }

  if (task->user_stack) {
    free(task->user_stack);
    task->user_stack = NULL;
  }
}

void task_context_switch(struct task *next) {
  struct task *prev = task_get_current();

  if (prev == next)
    return;

  ASSERT(prev);
  ASSERT(prev->context);
  ASSERT(next);
  ASSERT(next->context);

  task_set_current(next);
  task_cpu_switch(prev->context, next->context);
  task_clean_up(prev);
}

void task_schedule(void) {
  struct task *current = task_get_current();

  ASSERT(current);
  current->ticks = 0;

  task_schedule_loop();
}

void task_schedule_tail(void) { task_preempt_enable(); }

void task_preempt_enable(void) {
  struct task *current = task_get_current();

  ASSERT(current);
  current->preempt--;
}

void task_preempt_disable(void) {
  struct task *current = task_get_current();

  ASSERT(current);
  current->preempt++;
}

uint64_t task_get_priority(void) {
  struct task *current = task_get_current();

  ASSERT(current);
  return current->priority;
}

void task_exit(void) {
  struct task *current;

  task_preempt_disable();

  current = task_get_current();
  ASSERT(current);
  current->state = TASK_ZOMBIE;

  task_preempt_enable();
  task_schedule();
}
