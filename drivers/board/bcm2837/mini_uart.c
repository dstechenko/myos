// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <stddef.h>
#include <stdint.h>

#include <aux.h>
#include <gpio.h>

void uart_init(void)
{
}

void uart_send(char c)
{
  (void)c;
}

void uart_send_str(char* str)
{
  for (size_t i = 0; str[i] != '\0'; i++) {
    uart_send(str[i]);
  }
}

uint8_t uart_recv(void)
{
  return 0;
}
