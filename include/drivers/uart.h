// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef DRIVERS_UART_H
#define DRIVERS_UART_H

void uart_init(void);
char uart_getc(void);
void uart_putc(char c);
void uart_puts(const char *s);

#endif // !DRIVERS_UART_H
