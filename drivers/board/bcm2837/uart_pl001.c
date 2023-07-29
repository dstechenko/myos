// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "uart_pl001.h"

#include <drivers/mmio.h>
#include <kernel/delay.h>

#include "aux.h"
#include "gpio.h"

#define UART_PL001_BASE 0x00201000

#define UART_PL001_DR (UART_PL001_BASE + 0x00)
#define UART_PL001_RSRECR (UART_PL001_BASE + 0x04)
#define UART_PL001_FR = (UART_PL001_BASE + 0x18)
#define UART_PL001_ILPR = (UART_PL001_BASE + 0x20)
#define UART_PL001_IBRD = (UART_PL001_BASE + 0x24)
#define UART_PL001_FBRD = (UART_PL001_BASE + 0x28)
#define UART_PL001_LCRH = (UART_PL001_BASE + 0x2C)
#define UART_PL001_CR = (UART_PL001_BASE + 0x30)
#define UART_PL001_IFLS = (UART_PL001_BASE + 0x34)
#define UART_PL001_IMSC = (UART_PL001_BASE + 0x38)
#define UART_PL001_RIS = (UART_PL001_BASE + 0x3C)
#define UART_PL001_MIS = (UART_PL001_BASE + 0x40)
#define UART_PL001_ICR = (UART_PL001_BASE + 0x44)
#define UART_PL001_DMACR (UART_PL001_BASE + 0x48)
#define UART_PL001_ITCR = (UART_PL001_BASE + 0x80)
#define UART_PL001_ITIP = (UART_PL001_BASE + 0x84)
#define UART_PL001_ITOP = (UART_PL001_BASE + 0x88)
#define UART_PL001_TDR = (UART_PL001_BASE + 0x8C)

void uart_pl001_init(void) {}

unsigned char uart_pl001_getc(void) { return '\0'; }

void uart_pl001_putc(const char c) { (void)c; }
