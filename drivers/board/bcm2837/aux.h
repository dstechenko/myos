// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef DRIVERS_BOARD_BCM2837_AUX_H
#define DRIVERS_BOARD_BCM2837_AUX_H

/**
 * Auxiliary peripherals register map.
 * The Device has three Auxiliary peripherals: One mini UART and two SPI
 * masters. These three peripheral are grouped together as they share the same
 * area in the peripheral register map and they share a common interrupt. Also
 * all three are controlled by the auxiliary enable register.
 */

#define AUX_BASE 0x00215000

#define AUX_IRQ (AUX_BASE + 0x00)
#define AUX_ENABLES (AUX_BASE + 0x04)
#define AUX_MU_IO_REG (AUX_BASE + 0x40)
#define AUX_MU_IER_REG (AUX_BASE + 0x44)
#define AUX_MU_IIR_REG (AUX_BASE + 0x48)
#define AUX_MU_LCR_REG (AUX_BASE + 0x4C)
#define AUX_MU_MCR_REG (AUX_BASE + 0x50)
#define AUX_MU_LSR_REG (AUX_BASE + 0x54)
#define AUX_MU_MSR_REG (AUX_BASE + 0x58)
#define AUX_MU_SCRATCH (AUX_BASE + 0x5C)
#define AUX_MU_CNTL_REG (AUX_BASE + 0x60)
#define AUX_MU_STAT_REG (AUX_BASE + 0x64)
#define AUX_MU_BAUD_REG (AUX_BASE + 0x68)
#define AUX_SPI1_CNTL0_REG (AUX_BASE + 0x80)
#define AUX_SPI1_CNTL1_REG (AUX_BASE + 0x84)
#define AUX_SPI1_STAT_REG (AUX_BASE + 0x88)
#define AUX_SPI1_IO_REG (AUX_BASE + 0x90)
#define AUX_SPI1_PEEK_REG (AUX_BASE + 0x94)
#define AUX_SPI2_CNTL0_REG (AUX_BASE + 0xC0)
#define AUX_SPI2_CNTL1_REG (AUX_BASE + 0xC4)
#define AUX_SPI2_STAT_REG (AUX_BASE + 0xC8)
#define AUX_SPI2_IO_REG (AUX_BASE + 0xD0)
#define AUX_SPI2_PEEK_REG (AUX_BASE + 0xD4)

#endif // DRIVERS_BOARD_BCM2837_AUX_H
