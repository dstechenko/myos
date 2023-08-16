// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <drivers/timer.h>

#include <drivers/mmio.h>
#include <kernel/config.h>
#include <kernel/log.h>

#include "timer.h"

static uint64_t timer_ticks = 0;
static uint32_t timer_value = 0;

static void timer_tick(void) {
  timer_ticks++;
  timer_value += CONFIG_SYSTEM_TIMER_FREQ;
  mmio_write32(TIMER_C1, timer_value);
}

void timer_init(void) {
  timer_ticks = 0;
  timer_value = mmio_read32(TIMER_CLO);
  timer_tick();
}

void timer_handle(void) {
  log_debug("System timer ticks: %x, value: %x", timer_ticks, timer_value);
  timer_tick();
  mmio_write32(TIMER_CS, TIMER_CS_M1);
}
