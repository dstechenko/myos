// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "timer.h"

#include <drivers/mmio.h>
#include <drivers/timer.h>
#include <kernel/cpu.h>
#include <kernel/task.h>

#include <kernel/log.h>

static volatile uint64_t timer_ticks = 0;
static volatile uint32_t timer_value = 0;
static volatile bool timer_called = false;

static void timer_update(void) {
  timer_value += 100000000;
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
  timer_called = true;
  if (cpu_is_primary()) {
    timer_tick();
    mmio_write32(TIMER_CS, TIMER_CS_M0);
  }
  task_tick();
}

uint64_t timer_get_ticks(void) {
  return timer_ticks;
}

void timer_debug(void) {
  LOG_DEBUG("# TIMER_CS    = %x", mmio_read32(TIMER_CS));
  LOG_DEBUG("# TIMER_CLO   = %x", mmio_read32(TIMER_CLO));
  LOG_DEBUG("# TIMER_C1    = %x", mmio_read32(TIMER_C1));
  LOG_DEBUG("# value       = %x", timer_value);
  LOG_DEBUG("# called      = %x", timer_called);
  LOG_DEBUG("# IRQ_STATUS0 = %x", mmio_read32(0x0000B230));
}
