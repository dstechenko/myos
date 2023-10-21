// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "mbox.h"

#include <asm/delay.h>
#include <drivers/mmio.h>
#include <kernel/util/bits.h>

#define MBOX_BASE 0x0000B880
#define MBOX_RESPONSE 0x80000000
#define MBOX_FULL 0x80000000
#define MBOX_EMPTY 0x40000000

#define MBOX_READ (MBOX_BASE + 0x00)
#define MBOX_POLL (MBOX_BASE + 0x10)
#define MBOX_SENDER (MBOX_BASE + 0x14)
#define MBOX_STATUS (MBOX_BASE + 0x18)
#define MBOX_CONFIG (MBOX_BASE + 0x1C)
#define MBOX_WRITE (MBOX_BASE + 0x20)

int mbox_send(const unsigned char channel, const mbox_data_t *data) {
  unsigned int msg;

  // TODO(dstechenko): add asserts...

  // Wait until we can write to the mailbox.
  while (mmio_read32(MBOX_STATUS) & MBOX_FULL)
    // TODO(dstechenko): replace with NOPs?
    cdelay(1);

  // Write the address of the message and channel identifier.
  msg = ((uintptr_t)data & ~0xF) | MASK_LOW_HALF_BYTE(channel);
  mmio_write32(MBOX_WRITE, msg);

  // Send the message and wait for the response, check if ours/valid.
  while ((mmio_read32(MBOX_STATUS) & MBOX_EMPTY) || (mmio_read32(MBOX_READ) != msg))
    // TODO(dstechenko): replace with NOPs?
    cdelay(1);

  return data[1] == MBOX_RESPONSE;
}
