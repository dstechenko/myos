// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "timer.h"

#include <drivers/mmio.h>
#include <drivers/timer.h>
#include <kernel/config.h>
#include <kernel/cpu.h>
#include <kernel/task.h>

// TODO(dstechenko): make it work with multiple cores

// Actual system timer ticks CONFIG_BCM2711_SYSTEM_TIMER_FREQ times per second.
// We use CONFIG_SYSTEM_TIMER_FREQ to set how many times per second timer update
// happens and hence sets the frequency of the timer subsystem handler.
#define TICK_VALUE (CONFIG_BCM2711_SYSTEM_TIMER_FREQ / CONFIG_SYSTEM_TIMER_FREQ)

static volatile uint64_t timer_ticks = 0;
static volatile uint32_t timer_value = 0;

static void timer_update(void) {
  timer_value += TICK_VALUE;
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
