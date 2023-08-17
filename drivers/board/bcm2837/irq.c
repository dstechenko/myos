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
  log_debug("Enabling system timer interrupt #3");
  mmio_write32(IRQ_ENABLE_1, IRQ_TABLE_SYSTEM_TIMER_3);
}

void irq_handle(void) {
  uint32_t irq = mmio_read32(IRQ_PENDING_1);
  while (irq) {
    if (irq & IRQ_TABLE_SYSTEM_TIMER_1) {
      irq &= ~IRQ_TABLE_SYSTEM_TIMER_1;
      timer_handle();
    }
    if (irq & IRQ_TABLE_SYSTEM_TIMER_3) {
      irq &= ~IRQ_TABLE_SYSTEM_TIMER_3;
      // TODO: add handling for timer 3...
    }
  }
}
