// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef DRIVERS_BOARD_BCM2837_UART_PL001_H
#define DRIVERS_BOARD_BCM2837_UART_PL001_H

void uart_pl001_init(void);
char uart_pl001_getc(void);
void uart_pl001_putc(char c);

#endif // !DRIVERS_BOARD_BCM2837_UART_PL001_H
