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

#define AUX_IRQ 0x00215000
#define AUX_ENABLES 0x00215004
#define AUX_MU_IO_REG 0x00215040
#define AUX_MU_IER_REG 0x00215044
#define AUX_MU_IIR_REG 0x00215048
#define AUX_MU_LCR_REG 0x0021504C
#define AUX_MU_MCR_REG 0x00215050
#define AUX_MU_LSR_REG 0x00215054
#define AUX_MU_MSR_REG 0x00215058
#define AUX_MU_SCRATCH 0x0021505C
#define AUX_MU_CNTL_REG 0x00215060
#define AUX_MU_STAT_REG 0x00215064
#define AUX_MU_BAUD_REG 0x00215068
#define AUX_SPI1_CNTL0_REG 0x00215080
#define AUX_SPI1_CNTL1_REG 0x00215084
#define AUX_SPI1_STAT_REG 0x00215088
#define AUX_SPI1_IO_REG 0x00215090
#define AUX_SPI1_PEEK_REG 0x00215094
#define AUX_SPI2_CNTL0_REG 0x002150C0
#define AUX_SPI2_CNTL1_REG 0x002150C4
#define AUX_SPI2_STAT_REG 0x002150C8
#define AUX_SPI2_IO_REG 0x002150D0
#define AUX_SPI2_PEEK_REG 0x002150D4

#endif // DRIVERS_BOARD_BCM2837_AUX_H
