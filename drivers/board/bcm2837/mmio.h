// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef DRIVERS_BOARD_BCM2837_MMIO_H
#define DRIVERS_BOARD_BCM2837_MMIO_H

#include <asm/memory.h>
#include <kernel/core/config.h>

/**
 * ARM physical addresses for peripherals range from 0x3F000000 to 0x3FFFFFFF.
 * The bus addresses for peripherals are set up to map onto the peripheral
 * bus address range starting at 0x7E000000.
 */

#define MMIO_BASE CONFIG_BCM2837_DEVICE_MEMORY_LOW

#endif // !DRIVERS_BOARD_BCM2837_MMIO_H
