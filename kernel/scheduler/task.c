// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/scheduler/task.h>

#include <stddef.h>

#include <asm/irq.h>
#include <kernel/util/assert.h>

#define TASKS_TOTAL CONFIG_KERNEL_SCHEDULER_TASKS

static size_t tasks_next_id = 1;
static struct task tasks_init = {
    .context = NULL,
    .state = TASK_RUNNING,
    .ticks = 0,
    .priority = CONFIG_KERNEL_SCHEDULER_PRIORITY,
    .preempt = 0,
};

static struct task *tasks_current = &tasks_init;
static struct task *tasks_all[TASKS_TOTAL] = {&tasks_init};

int task_init(void) { return task_context_init(&tasks_init); }

void task_schedule_loop(void) {
  task_preempt_disable();
  task_context_switch(task_pick());
  task_preempt_enable();
}

void task_enqueue(struct task *task) {
  ASSERT(task);
  ASSERT(tasks_next_id < TASKS_TOTAL);
  tasks_all[tasks_next_id++] = task;
}

void task_dequeue(struct task *task) { ASSERT(task); }

void task_tick(void) {
  ASSERT(tasks_current);
  tasks_current->ticks--;
  if (tasks_current->ticks > 0 || tasks_current->preempt > 0)
    return;
  irq_enable();
  task_schedule();
  irq_disable();
}

struct task *task_pick(void) {
  size_t id;
  int64_t ticks;
  struct task *each, *next;

  while (true) {
    next = &tasks_init;
    ticks = next->ticks;
    for (id = 0; id < TASKS_TOTAL; id++) {
      each = tasks_all[id];
      if (each && each->state == TASK_RUNNING && each->ticks > ticks) {
        ticks = each->ticks;
        next = each;
      }
    }
    if (ticks)
      break;
    for (id = 0; id < TASKS_TOTAL; id++) {
      each = tasks_all[id];
      if (each)
        each->ticks = (each->ticks >> 1) + each->priority;
    }
  }

  return next;
}

void task_context_switch(struct task *next) {
  struct task *prev;

  if (tasks_current == next)
    return;

  prev = tasks_current, tasks_current = next;
  ASSERT(prev && prev->context);
  ASSERT(next && next->context);
  task_cpu_switch(prev->context, next->context);
}

void task_schedule(void) {
  ASSERT(tasks_current);
  tasks_current->ticks = 0;
  task_schedule_loop();
}

void task_schedule_tail(void) { task_preempt_enable(); }

void task_preempt_enable(void) {
  ASSERT(tasks_current);
  tasks_current->preempt--;
}

void task_preempt_disable(void) {
  ASSERT(tasks_current);
  tasks_current->preempt++;
}

uint64_t task_get_priority(void) {
  ASSERT(tasks_current);
  return tasks_current->priority;
}
