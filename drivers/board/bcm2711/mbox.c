// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "mbox.h"

#include <asm/delay.h>

#include <drivers/mmio.h>

#include <kernel/assert.h>
#include <kernel/bits.h>

int mbox_send(const unsigned char channel, const mbox_data_t *data) {
  unsigned int msg;

  ASSERT(data);

  // Wait until we can write to the mailbox.
  while (mmio_read32(MBOX_STATUS) & MBOX_FULL) {
    delay_noop();
  }

  // Write the address of the message and channel identifier.
  msg = ((uintptr_t)data & ~0xF) | MASK_LOW_HALF_BYTE(channel);
  mmio_write32(MBOX_WRITE, msg);

  // Send the message and wait for the response, check if ours/valid.
  while ((mmio_read32(MBOX_STATUS) & MBOX_EMPTY) || (mmio_read32(MBOX_READ) != msg)) {
    delay_noop();
  }

  return data[1] == MBOX_RESPONSE;
}
