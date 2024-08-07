// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef DRIVERS_BOARD_BCM2711_UART_MINI_H
#define DRIVERS_BOARD_BCM2711_UART_MINI_H

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

void uart_mini_init(void);
char uart_mini_getc(void);
void uart_mini_putc(char c);

#endif  // !DRIVERS_BOARD_BCM2711_UART_MINI_H
