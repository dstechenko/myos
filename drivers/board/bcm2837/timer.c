// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <drivers/timer.h>

#include <drivers/mmio.h>
#include <kernel/task.h>

#include "timer.h"

static volatile uint64_t timer_ticks = 0;
static volatile uint32_t timer_value = 0;

static void timer_update(void) {
  timer_value += CONFIG_SYSTEM_TIMER_FREQ;
  mmio_write32(TIMER_C1, timer_value);
}

static void timer_tick(void) {
  timer_ticks++;
  timer_update();
}

void timer_init(void) {
  timer_ticks = 0;
  timer_value = mmio_read32(TIMER_CLO);
  timer_update();
}

void timer_handle(void) {
  timer_tick();
  mmio_write32(TIMER_CS, TIMER_CS_M1);
  task_tick();
}

uint64_t timer_get_ticks(void) { return timer_ticks; }
