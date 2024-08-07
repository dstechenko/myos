// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "irq.h"

#include <drivers/irq.h>
#include <drivers/mmio.h>

#include "timer.h"

void irq_init(void) { mmio_write32(IRQ_ENABLE_0, IRQ_TABLE_SYSTEM_TIMER_1); }

void irq_handle(void) {
  uint32_t irq = mmio_read32(IRQ_PENDING_0);

  while (irq) {
    if (irq & IRQ_TABLE_SYSTEM_TIMER_1) {
      irq &= ~IRQ_TABLE_SYSTEM_TIMER_1;
      timer_handle();
    }
  }
}
