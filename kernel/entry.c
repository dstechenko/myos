// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/entry.h>

#include <drivers/uart.h>
#include <kernel/build_info.h>

void kernel_entry(void)
{
	uart_init();
	uart_puts("MyOS boot complete!\r\n");
	uart_puts("Build commit hash:   ");
	uart_puts(BUILD_INFO_COMMIT_HASH);
	uart_puts("\r\n");
	uart_puts("Build timestamp:     ");
	uart_puts(BUILD_INFO_TIMESTAMP);
	uart_puts("\r\n");
	uart_puts("Build target arch:   ");
	uart_puts(BUILD_INFO_TARGET_ARCH);
	uart_puts("\r\n");
	uart_puts("Build target board:  ");
	uart_puts(BUILD_INFO_TARGET_BOARD);
	uart_puts("\r\n");
	uart_puts("Build target mode:   ");
	uart_puts(BUILD_INFO_TARGET_MODE);
	uart_puts("\r\n");
	uart_puts("Build host arch:     ");
	uart_puts(BUILD_INFO_HOST_ARCH);
	uart_puts("\r\n");
	uart_puts("Spinning now...\r\n");
}
