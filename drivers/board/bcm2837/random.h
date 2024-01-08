// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef DRIVERS_BOARD_BCM2837_RANDOM_H
#define DRIVERS_BOARD_BCM2837_RANDOM_H

#define RANDOM_BASE 0x00104000
#define RANDOM_CTRL RANDOM_BASE
#define RANDOM_STATUS (RANDOM_BASE + 0x04)
#define RANDOM_DATA (RANDOM_BASE + 0x08)
#define RANDOM_IRQ_MASK (RANDOM_BASE + 0x10)

#define RANDOM_STATUS_INIT 0x40000
#define RANDOM_READY_SHIFT 24

void random_init(void);

#endif  // !DRIVERS_BOARD_BCM2837_RANDOM_H
