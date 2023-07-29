// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "uart_pl001.h"

#include <drivers/mmio.h>
#include <kernel/delay.h>

#include "aux.h"
#include "gpio.h"

void uart_pl001_init(void) {}

unsigned char uart_pl001_getc(void) { return '\0'; }

void uart_pl001_putc(const char c) { (void)c; }
