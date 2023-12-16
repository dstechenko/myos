// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <drivers/random.h>

#include <asm/delay.h>
#include <drivers/mmio.h>
#include <kernel/bits.h>
#include <uapi/bool.h>

#include "random.h"

void random_init(void) {
  const uint32_t random_irq_masked = mmio_read32(RANDOM_IRQ_MASK) | BIT(0);
  const uint32_t random_ctrl_enabled = mmio_read32(RANDOM_CTRL) | BIT(0);

  mmio_write32(RANDOM_STATUS, RANDOM_STATUS_INIT);
  mmio_write32(RANDOM_IRQ_MASK, random_irq_masked);
  mmio_write32(RANDOM_CTRL, random_ctrl_enabled);
}

static bool random_is_ready(void) {
  return mmio_read32(RANDOM_STATUS) >> RANDOM_READY_SHIFT;
}

static uint32_t random_get_data(const uint32_t min, const uint32_t max) {
  return mmio_read32(RANDOM_DATA) % (max - min) + min;
}

uint32_t random_get(const uint32_t min, const uint32_t max) {
  // Need to wait for entropy: bits 24-31 store the number of words ready.
  while (!random_is_ready()) delay_nop();
  return random_get_data(min, max);
}
