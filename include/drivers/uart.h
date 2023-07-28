// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef DRIVERS_UART_H
#define DRIVERS_UART_H

void uart_init(void);
unsigned char uart_recv(void);
void uart_send(char c);
void uart_send_str(const char *s);

#endif // DRIVERS_UART_H
