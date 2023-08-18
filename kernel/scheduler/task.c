// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/scheduler/task.h>

#include <stddef.h>

#include <asm/irq.h>
#include <kernel/util/assert.h>

#define NR_TASKS 64

static DEFINE_TASK(init);

static size_t next_id = 1;
static struct task *current = &init;
static struct task *all[NR_TASKS] = {&init};

void task_schedule_loop(void) {
  size_t id;
  int64_t ticks;
  struct task *each, *next;

  task_preempt_disable();

  while (true) {
    next = &init;
    ticks = next->ticks;
    for (id = 0; id < NR_TASKS; id++) {
      each = all[id];
      if (each && each->state == TASK_RUNNING && each->ticks > ticks) {
        ticks = each->ticks;
        next = each;
      }
    }
    if (ticks)
      break;
    for (id = 0; id < NR_TASKS; id++) {
      each = all[id];
      if (each)
        each->ticks = (each->ticks >> 1) + each->priority;
    }
  }

  task_context_switch(next);
  task_preempt_enable();
}

void task_add(struct task *task) {
  ASSERT(task);
  ASSERT(next_id < NR_TASKS);
  all[next_id++] = task;
}

void task_schedule(void) {
  ASSERT(current);
  current->ticks = 0;
  task_schedule_loop();
}

void task_schedule_tick(void) {
  ASSERT(current);
  current->ticks--;
  if (current->ticks > 0 || current->preempt > 0)
    return;
  irq_enable();
  task_schedule();
  irq_disable();
}

void task_context_switch(struct task *next) {
  struct task *prev;

  ASSERT(next);
  ASSERT(current);
  if (current == next)
    return;

  prev = current, current = next;
  task_cpu_context_switch(&prev->context, &next->context);
}

void task_schedule_tail(void) { task_preempt_enable(); }

void task_preempt_enable(void) {
  ASSERT(current);
  current->preempt--;
}

void task_preempt_disable(void) {
  ASSERT(current);
  current->preempt++;
}

uint64_t task_get_priority(void) {
  ASSERT(current);
  return current->priority;
}
