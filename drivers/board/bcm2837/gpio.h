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

#define GPFSEL0 0x00200000
#define GPFSEL1 0x00200004
#define GPFSEL2 0x00200008
#define GPFSEL3 0x0020000C
#define GPFSEL4 0x00200010
#define GPFSEL5 0x00200014
#define GPSET0 0x0020001C
#define GPSET1 0x00200020
#define GPCLR0 0x00200028
#define GPCLR1 0x0020002C
#define GPPUD 0x00200094
#define GPPUDCLK0 0x00200098

#endif // DRIVERS_BOARD_BCM2837_GPIO_H
