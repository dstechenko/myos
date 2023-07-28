// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/entry.h>

#include <drivers/uart.h>

void kernel_entry(void)
{
  uart_init();
  uart_send_str("MyOS boot complete!\r\n");
}
