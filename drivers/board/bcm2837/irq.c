// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <drivers/irq.h>

#include <drivers/mmio.h>
#include <drivers/timer.h>
#include <kernel/log.h>

#include "irq.h"

void irq_ctrl_init(void) {
  log_debug("Programming interrupt controller");
  log_debug("Enabling system timer interrupt #1");
  mmio_write32(IRQ_ENABLE_1, IRQ_TABLE_SYSTEM_TIMER_1);
}

void irq_handle(void) {
  const uint32_t irq = mmio_read32(IRQ_PENDING_1);
  switch (irq) {
  case IRQ_TABLE_SYSTEM_TIMER_1:
    timer_handle();
    break;
  default:
    log_error("Unknown pending interrupt request: %x", irq);
  }
}
