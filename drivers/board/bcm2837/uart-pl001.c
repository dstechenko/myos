// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "uart-pl001.h"

#include <stdint.h>

#include <asm/delay.h>
#include <drivers/mmio.h>
#include <kernel/bits.h>
#include <kernel/config.h>

#include "aux.h"
#include "gpio.h"
#include "mbox.h"

/**
 * If you use a particular pin as input and don't connect anything to this pin,
 * you will not be able to identify whether the value of the pin is 1 or 0.
 * In fact, the device will report random values.
 * The pull-up/pull-down mechanism allows you to overcome this issue.
 * If you set the pin to the pull-up state and nothing is connected to it, it
 * will report 1 all the time (for the pull-down state, the value will always
 * be 0). In our case, we need neither the pull-up nor the pull-down state,
 * because both the 14 and 15 pins are going to be connected all the time. The
 * pin state is preserved even after a reboot, so before using any pin, we
 * always have to initialize its state. There are three available states:
 * pull-up, pull-down, and neither (to remove the current pull-up or pull-down
 * state), and we need the third one.
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
  mbox[6] = CONFIG_BCM2837_SYSTEM_CLOCK_FREQ;
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
  reg = CONFIG_BCM2837_SYSTEM_CLOCK_FREQ / (16 * CONFIG_BCM2837_UART_BAUDRATE);
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
    delay_nop();
  }
  return MASK_LOW_BYTE(mmio_read32(UART_PL001_DR));
}

void uart_pl001_putc(const char c) {
  while (mmio_read32(UART_PL001_FR) & BIT(5)) {
    delay_nop();
  }
  mmio_write32(UART_PL001_DR, c);
}
