// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef DRIVERS_BOARD_BCM2837_MMIO_BASE
#define DRIVERS_BOARD_BCM2837_MMIO_BASE

/**
 * ARM physical addresses for peripherals range from 0x3F000000 to 0x3FFFFFFF.
 * The bus addresses for peripherals are set up to map onto the peripheral
 * bus address range starting at 0x7E000000.
 */

#define MMIO_BASE 0x3F000000

#endif // !DRIVERS_BOARD_BCM2837_MMIO_BASE
