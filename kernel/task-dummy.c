// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/task.h>

#include <stddef.h>

#include <asm/irq.h>
#include <kernel/assert.h>

#include "task-main.h"

#define TASKS_TOTAL CONFIG_KERNEL_SCHEDULER_TASKS

static uint64_t tasks_next_id = 1;
static struct task tasks_main = INIT_TASK_MAIN(tasks_main);

static struct task *tasks_current = &tasks_main;
static struct task *tasks_all[TASKS_TOTAL] = {NULL};

int task_main_init(void) {
  tasks_all[0] = &tasks_main;
  return task_init(&tasks_main);
}

int task_enqueue(struct task *task) {
  ASSERT(task);
  ASSERT(tasks_next_id < TASKS_TOTAL);
  task->id = tasks_next_id;
  tasks_all[tasks_next_id++] = task;
  return 0;
}

void task_dequeue(struct task *task) { ASSERT(task); }

void task_tick(void) {
  ASSERT(tasks_current);
  tasks_current->ticks--;
  if (tasks_current->ticks > 0 || tasks_current->preempt > 0)
    return;
  local_irq_enable();
  task_schedule();
  local_irq_disable();
}

struct task *task_pick(void) {
  size_t id;
  int64_t ticks;
  struct task *each, *next;

  while (true) {
    next = &tasks_main;
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
      if (each && each->state == TASK_RUNNING)
        each->ticks = (each->ticks >> 1) + each->priority;
    }
  }

  return next;
}

struct task *task_get_current(void) { return tasks_current; }

void task_set_current(struct task *task) { tasks_current = task; }
