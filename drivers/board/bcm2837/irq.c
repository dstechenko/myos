// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <drivers/irq.h>

#include <drivers/mmio.h>
#include <drivers/timer.h>
#include <kernel/logging/log.h>

#include "irq.h"

void irq_ctrl_init(void) { mmio_write32(IRQ_ENABLE_1, IRQ_TABLE_SYSTEM_TIMER_1); }

void irq_handle(void) {
  uint32_t irq = mmio_read32(IRQ_PENDING_1);
  while (irq) {
    if (irq & IRQ_TABLE_SYSTEM_TIMER_1) {
      irq &= ~IRQ_TABLE_SYSTEM_TIMER_1;
      timer_handle();
    }
    if (irq & IRQ_TABLE_SYSTEM_TIMER_3) {
      irq &= ~IRQ_TABLE_SYSTEM_TIMER_3;
    }
  }
}
