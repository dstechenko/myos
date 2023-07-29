// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "uart_mini.h"

#include <drivers/mmio.h>
#include <kernel/delay.h>

#include "aux.h"
#include "gpio.h"

void uart_mini_init(void)
{
	unsigned int selector;

	selector = mmio_read32(GPFSEL1);
	// clean gpio14
	selector &= ~(7 << 12);
	// set alt5 for gpio14
	selector |= 2 << 12;
	// clean gpio15
	selector &= ~(7 << 15);
	// set alt5 for gpio15
	selector |= 2 << 15;
	mmio_write32(GPFSEL1, selector);

	mmio_write32(GPPUD, 0);
	cdelay(150);
	mmio_write32(GPPUDCLK0, (1 << 14) | (1 << 15));
	cdelay(150);
	mmio_write32(GPPUDCLK0, 0);

	// Enable Mini UART (this also enables access to its registers).
	mmio_write32(AUX_ENABLES, 1);
	// Disable auto flow control and disable receiver/transmitter (for now).
	mmio_write32(AUX_MU_CNTL_REG, 0);
	// Disable receive/transmit interrupts.
	mmio_write32(AUX_MU_IER_REG, 0);
	// Enable 8 bit mode.
	mmio_write32(AUX_MU_LCR_REG, 3);
	// Set RTS line to be always high.
	mmio_write32(AUX_MU_MCR_REG, 0);
	// Set baud rate to 115200.
	mmio_write32(AUX_MU_BAUD_REG, 270);
	// Finally, enable receiver/transmitter.
	mmio_write32(AUX_MU_CNTL_REG, 3);
}

unsigned char uart_mini_getc(void)
{
	while (1) {
		if (mmio_read32(AUX_MU_LSR_REG) & 0x01)
			break;
	}
	return (mmio_read32(AUX_MU_IO_REG) & 0xFF);
}

void uart_mini_putc(const char c)
{
	while (1) {
		if (mmio_read32(AUX_MU_LSR_REG) & 0x20)
			break;
	}
	mmio_write32(AUX_MU_IO_REG, c);
}
