// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "uart-pl001.h"

#include <asm/delay.h>

#include <drivers/mmio.h>

#include <kernel/bits.h>
#include <kernel/config.h>
#include <kernel/types.h>

#include "aux.h"
#include "gpio.h"
#include "mbox.h"

void uart_pl001_init(void) {
  uint32_t reg;

  // Disable UART_PL001.
  mmio_write32(UART_PL001_CR, 0);

  // Set up clock for consistent divisor values.
  DEFINE_MBOX(mbox);

  // Set clock rate.
  mbox[0] = 9 * 4;
  mbox[1] = MBOX_REQUEST;
  mbox[2] = MBOX_TAG_SET_CLKRATE;
  mbox[3] = 12;
  mbox[4] = 8;
  // UART clock with 4Mhz and cleared turbo.
  mbox[5] = 2;
  mbox[6] = CONFIG_BCM2711_SYSTEM_CLOCK_FREQ;
  mbox[7] = 0;
  mbox[8] = MBOX_TAG_LAST;

  mbox_send(MBOX_CHANNEL_PROP, mbox);

  // GPIO pins should be set up first the before enabling the UART.
  reg = mmio_read32(GPFSEL1);
  // Clean and set alt5 for pin 14.
  reg &= ~(7 << 12);
  reg |= 2 << 12;
  // Clean and set alt5 for pin 15.
  reg &= ~(7 << 15);
  reg |= 2 << 15;
  mmio_write32(GPFSEL1, reg);
  // Remove pull-up/down state from pins 14,15 and flush it.
  mmio_write32(GPPUD, 0);
  delay_cycles(150);
  mmio_write32(GPPUDCLK0, BIT(14) | BIT(15));
  delay_cycles(150);
  mmio_write32(GPPUDCLK0, 0);

  // Clear pending interrupts.
  mmio_write32(UART_PL001_ICR, 0x7FF);
  // Set integer_reg  = (system_clock_freq / (16 * baudrate)).
  reg = CONFIG_BCM2711_SYSTEM_CLOCK_FREQ / (16 * CONFIG_BCM2711_UART_BAUDRATE);
  mmio_write32(UART_PL001_IBRD, reg);
  // Set fraction_reg = (fractional_part * 64) + 0.5.
  // Let's try with 0 and if not - revisit to fix.
  reg = 0;
  mmio_write32(UART_PL001_FBRD, reg);
  // Enable FIFO and 8bit data transmission (1 stop bit, no parity).
  mmio_write32(UART_PL001_LCRH, BIT(4) | BIT(5) | BIT(6));
  // Enable UART_PL001, enable RX and TX part of it.
  mmio_write32(UART_PL001_CR, BIT(0) | BIT(8) | BIT(9));
}

char uart_pl001_getc(void) {
  while (mmio_read32(UART_PL001_FR) & BIT(4)) {
    delay_noop();
  }
  return MASK_LOW_BYTE(mmio_read32(UART_PL001_DR));
}

void uart_pl001_putc(const char c) {
  while (mmio_read32(UART_PL001_FR) & BIT(5)) {
    delay_noop();
  }
  mmio_write32(UART_PL001_DR, c);
}
