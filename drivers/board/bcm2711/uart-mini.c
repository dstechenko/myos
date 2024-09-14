// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "uart-mini.h"

#include <asm/delay.h>

#include <drivers/mmio.h>

#include <kernel/bits.h>
#include <kernel/config.h>
#include <kernel/types.h>

#include "aux.h"
#include "gpio.h"

void uart_mini_init(void) {
  uint32_t reg;

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
  // Calculated: baudrate = system_clock_freq / (8 * (baudrate_reg + 1)).
  reg = (CONFIG_BCM2711_SYSTEM_CLOCK_FREQ / (8 * CONFIG_BCM2711_UART_BAUDRATE)) - 1;
  mmio_write32(AUX_MU_BAUD_REG, reg);
  // Finally, enable receiver/transmitter.
  mmio_write32(AUX_MU_CNTL_REG, 3);
}

char uart_mini_getc(void) {
  while (true) {
    if (mmio_read32(AUX_MU_LSR_REG) & BIT(0)) {
      break;
    }
  }
  return (MASK_LOW_BYTE(mmio_read32(AUX_MU_IO_REG)));
}

void uart_mini_putc(const char c) {
  while (true) {
    if (mmio_read32(AUX_MU_LSR_REG) & BIT(5)) {
      break;
    }
  }
  mmio_write32(AUX_MU_IO_REG, c);
}
