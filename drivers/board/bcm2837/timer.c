// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <drivers/timer.h>

#include <drivers/mmio.h>
#include <kernel/config.h>
#include <kernel/log.h>

#include "timer.h"

static uint32_t counter = 0;

static void timer_tick(void) {
  counter += CONFIG_SYSTEM_TIMER_FREQ;
  mmio_write32(TIMER_C1, counter);
}

void timer_init(void) {
  counter = mmio_read32(TIMER_CLO);
  timer_tick();
}

void timer_handle(void) {
  log_debug("System timer interrupt, counter: %x", counter);
  timer_tick();
  mmio_write32(TIMER_CS, TIMER_CS_M1);
}
