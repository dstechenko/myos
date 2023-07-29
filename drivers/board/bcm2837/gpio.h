// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef DRIVERS_BOARD_BCM2837_GPIO_H
#define DRIVERS_BOARD_BCM2837_GPIO_H

/**
 * There are 54 general-purpose I/O (GPIO) lines split into two banks. All GPIO
 * pins have at least two alternative functions within BCM. The alternate
 * functions are usually peripheral IO and a single peripheral may appear in
 * each bank to allow flexibility on the choice of IO voltage. The GPIO
 * peripheral has three dedicated interrupt lines. These lines are triggered by
 * the setting of bits in the event detect status register. Each bank has its’
 * own interrupt line with the third line shared between all bits. The Alternate
 * function table also has the pull state (pull-up/pull-down) which is applied
 * after a power down.
 */

#define GPIO_BASE 0x00200000

#define GPFSEL0 (GPIO_BASE + 0x00)
#define GPFSEL1 (GPIO_BASE + 0x04)
#define GPFSEL2 (GPIO_BASE + 0x08)
#define GPFSEL3 (GPIO_BASE + 0x0C)
#define GPFSEL4 (GPIO_BASE + 0x10)
#define GPFSEL5 (GPIO_BASE + 0x14)
#define GPSET0 (GPIO_BASE + 0x1C)
#define GPSET1 (GPIO_BASE + 0x20)
#define GPCLR0 (GPIO_BASE + 0x28)
#define GPCLR1 (GPIO_BASE + 0x2C)
#define GPPUD (GPIO_BASE + 0x94)
#define GPPUDCLK0 (GPIO_BASE + 0x98)

#endif // DRIVERS_BOARD_BCM2837_GPIO_H
