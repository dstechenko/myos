// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef DRIVERS_BOARD_BCM2711_UART_PL001_H
#define DRIVERS_BOARD_BCM2711_UART_PL001_H

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

void uart_pl001_init(void);
char uart_pl001_getc(void);
void uart_pl001_putc(char c);

#endif  // !DRIVERS_BOARD_BCM2711_UART_PL001_H
