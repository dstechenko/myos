// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "uart_pl001.h"

#include <drivers/mmio.h>
#include <kernel/bits.h>
#include <kernel/delay.h>

#include "aux.h"
#include "gpio.h"

/**
 * If you use a particular pin as input and don't connect anything to this pin,
 * you will not be able to identify whether the value of the pin is 1 or 0.
 * In fact, the device will report random values.
 * The pull-up/pull-down mechanism allows you to overcome this issue.
 * If you set the pin to the pull-up state and nothing is connected to it, it
 * will report 1 all the time (for the pull-down state, the value will always be
 * 0). In our case, we need neither the pull-up nor the pull-down state, because
 * both the 14 and 15 pins are going to be connected all the time. The pin state
 * is preserved even after a reboot, so before using any pin, we always have to
 * initialize its state. There are three available states: pull-up, pull-down,
 * and neither (to remove the current pull-up or pull-down state), and we need
 * the third one.
 *
 * The GPIO pull-up/down clock registers control the actuation of internal
 * pull-downs on the respective GPIO pins. These registers must be used in
 * conjunction with the GPPUD register to effect GPIO pull-up/down changes. The
 * following sequence of events is required:
 * 1. Write to GPPUD to set the required control signal (i.e. pull-up or
 * pull-down or neither to remove the current pull-up/down).
 * 2. Wait 150 cycles – this provides the required set-up time for the control
 * signal.
 * 3. Write to GPPUDCLK0/1 to clock the control signal into the GPIO pads you
 * wish to modify – NOTE only the pads which receive a clock will be modified,
 * all others will retain their previous state.
 * 4. Wait 150 cycles – this provides the required hold time for the control
 * signal.
 * 5. Write to GPPUD to remove the control signal.
 * 6. Write to GPPUDCLK0/1 to remove the clock.
 */

#define UART_PL001_BASE 0x00201000

#define UART_PL001_DR (UART_PL001_BASE + 0x00)
#define UART_PL001_RSRECR (UART_PL001_BASE + 0x04)
#define UART_PL001_FR (UART_PL001_BASE + 0x18)
#define UART_PL001_ILPR (UART_PL001_BASE + 0x20)
#define UART_PL001_IBRD (UART_PL001_BASE + 0x24)
#define UART_PL001_FBRD (UART_PL001_BASE + 0x28)
#define UART_PL001_LCRH (UART_PL001_BASE + 0x2C)
#define UART_PL001_CR (UART_PL001_BASE + 0x30)
#define UART_PL001_IFLS (UART_PL001_BASE + 0x34)
#define UART_PL001_IMSC (UART_PL001_BASE + 0x38)
#define UART_PL001_RIS (UART_PL001_BASE + 0x3C)
#define UART_PL001_MIS (UART_PL001_BASE + 0x40)
#define UART_PL001_ICR (UART_PL001_BASE + 0x44)
#define UART_PL001_DMACR (UART_PL001_BASE + 0x48)
#define UART_PL001_ITCR (UART_PL001_BASE + 0x80)
#define UART_PL001_ITIP (UART_PL001_BASE + 0x84)
#define UART_PL001_ITOP (UART_PL001_BASE + 0x88)
#define UART_PL001_TDR (UART_PL001_BASE + 0x8C)

void uart_pl001_init(void)
{
	unsigned int gpio_reg;

	// Disable UART_PL001.
	mmio_write32(UART_PL001_CR, 0);

	// TODO: set up clock via mbox calls here...

	// GPIO pins should be set up first the before enabling the UART.
	gpio_reg = mmio_read32(GPFSEL1);
	// Clean and set alt5 for pin 14.
	gpio_reg &= ~(7 << 12);
	gpio_reg |= 2 << 12;
	// Clean and set alt5 for pin 15.
	gpio_reg &= ~(7 << 15);
	gpio_reg |= 2 << 15;
	mmio_write32(GPFSEL1, gpio_reg);
	// Remove pull-up/down state from pins 14,15 and flush it.
	mmio_write32(GPPUD, 0);
	cdelay(150);
	mmio_write32(GPPUDCLK0, (1 << 14) | (1 << 15));
	cdelay(150);
	mmio_write32(GPPUDCLK0, 0);

	// Clear pending interrupts.
	mmio_write32(UART_PL001_ICR, 0x7FF);

	// TODO: finish setup here...
}

unsigned char uart_pl001_getc(void)
{
	_Bool b = 1;
	while (b)
		if (mmio_read32(UART_PL001_FR) & BIT(4))
			break;
	return (MASK_LOW_BYTE(mmio_read32(AUX_MU_IO_REG)));
}

void uart_pl001_putc(const char c)
{
	_Bool b = 1;
	while (b)
		if (mmio_read32(UART_PL001_FR) & BIT(5))
			break;
	mmio_write32(UART_PL001_DR, c);
}
