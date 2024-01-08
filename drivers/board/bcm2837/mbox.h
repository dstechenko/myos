// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef DRIVERS_BOARD_BCM2837_MBOX_H
#define DRIVERS_BOARD_BCM2837_MBOX_H

#include <kernel/layout.h>

/**
 * Mailboxes facilitate communication between the ARM and the VideoCore.
 * This file lists the available mailboxes/channels.
 * Each mailbox is an 8-deep FIFO of 32-bit words, which can be
 * read(popped)/written(pushed) by the ARM and VC. Only mailbox 0's status can
 * trigger interrupts on the ARM, so MB 0 is always for communication from VC
 * to ARM and MB 1 is for ARM to VC. The ARM should never write MB 0 or read
 * MB 1.
 */

#define MBOX_REQUEST 0

#define MBOX_CHANNEL_POWER 0
#define MBOX_CHANNEL_FB 1
#define MBOX_CHANNEL_VUART 2
#define MBOX_CHANNEL_VCHIQ 3
#define MBOX_CHANNEL_LEDS 4
#define MBOX_CHANNEL_BTNS 5
#define MBOX_CHANNEL_TOUCH 6
#define MBOX_CHANNEL_COUNT 7
#define MBOX_CHANNEL_PROP 8

#define MBOX_TAG_GET_SERIAL 0x10004
#define MBOX_TAG_SET_CLKRATE 0x38002
#define MBOX_TAG_LAST 0

typedef volatile unsigned int mbox_data_t;

#define DEFINE_MBOX(name) mbox_data_t ALIGNED(16) name[36]

int mbox_send(unsigned char channel, const mbox_data_t *data);

#endif  // !DRIVERS_BOARD_BCM2837_MBOX_H
