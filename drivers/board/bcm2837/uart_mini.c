// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "uart_mini.h"

#include <drivers/mmio.h>
#include <kernel/bits.h>
#include <kernel/delay.h>
#include <kernel/kconfig.h>

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

void uart_mini_init(void)
{
  unsigned int selector;

  // GPIO pins should be set up first the before enabling the UART.
  selector = mmio_read32(GPFSEL1);
  // Clean and set alt5 for pin 14.
  selector &= ~(7 << 12);
  selector |= 2 << 12;
  // Clean and set alt5 for pin 15.
  selector &= ~(7 << 15);
  selector |= 2 << 15;
  mmio_write32(GPFSEL1, selector);

  // Remove pull-up/down state from pins 14,15 and flush it.
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
  // Calculated: baudrate = system_clock_freq / (8 * (baudrate_reg + 1)).
  // The system_clock_freq is 250 MHz, so the value of baudrate_reg should be 270.
  mmio_write32(AUX_MU_BAUD_REG, (CONFIG_SYSTEM_CLOCK_FREQ / (8 * CONFIG_UART_BAUDRATE)) - 1);
  // Finally, enable receiver/transmitter.
  mmio_write32(AUX_MU_CNTL_REG, 3);
}

unsigned char uart_mini_getc(void)
{
  _Bool b = 1;
  while (b)
    if (mmio_read32(AUX_MU_LSR_REG) & BIT(0))
      break;
  return (MASK_LOW_BYTE(mmio_read32(AUX_MU_IO_REG)));
}

void uart_mini_putc(const char c)
{
  _Bool b = 1;
  while (b)
    if (mmio_read32(AUX_MU_LSR_REG) & BIT(5))
      break;
  mmio_write32(AUX_MU_IO_REG, c);
}
