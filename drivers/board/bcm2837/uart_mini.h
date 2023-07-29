// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef DRIVERS_BOARD_BCM2837_UART_MINI_H
#define DRIVERS_BOARD_BCM2837_UART_MINI_H

void uart_mini_init(void);
unsigned char uart_mini_getc(void);
void uart_mini_putc(char c);

#endif // !DRIVERS_BOARD_BCM2837_UART_MINI_H
