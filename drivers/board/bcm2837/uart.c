// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <drivers/uart.h>

#include <stddef.h>

#include <kernel/config.h>

#if CONFIG_ENABLED(CONFIG_UART_USE_MINI)
#include "uart_mini.h"
#else // !CONFIG_ENABLED(CONFIG_UART_USE_MINI)
#include "uart_pl001.h"
#endif // CONFIG_ENABLED(CONFIG_UART_USE_MINI)

void uart_init(void)
{
#if CONFIG_ENABLED(CONFIG_UART_USE_MINI)
	uart_mini_init();
#else  // !CONFIG_ENABLED(CONFIG_UART_USE_MINI)
	uart_pl001_init();
#endif // CONFIG_ENABLED(CONFIG_UART_USE_MINI)
}

char uart_getc(void)
{
	// TODO: convert \r -> \n?
#if CONFIG_ENABLED(CONFIG_UART_USE_MINI)
	return uart_mini_getc();
#else  // !CONFIG_ENABLED(CONFIG_UART_USE_MINI)
	return uart_pl001_getc();
#endif // CONFIG_ENABLED(CONFIG_UART_USE_MINI)
}

void uart_putc(const char c)
{
// TODO: convert \n -> \r\n?
#if CONFIG_ENABLED(CONFIG_UART_USE_MINI)
	uart_mini_putc(c);
#else  // !CONFIG_ENABLED(CONFIG_UART_USE_MINI)
	uart_pl001_putc(c);
#endif // CONFIG_ENABLED(CONFIG_UART_USE_MINI)
}

void uart_puts(const char *s)
{
	for (size_t i = 0; s[i] != '\0'; i++) {
		uart_putc(s[i]);
	}
}
