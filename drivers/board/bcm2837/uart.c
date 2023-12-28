// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <drivers/uart.h>

#include <stddef.h>

#include <kernel/config.h>
#include <kernel/spinlock.h>

static spinlock_t uart_lock;

#if CONFIG_ENABLED(CONFIG_BCM2837_UART_USE_MINI)
#include "uart-mini.h"
#else // !CONFIG_ENABLED(CONFIG_BCM2837_UART_USE_MINI)
#include "uart-pl001.h"
#endif // CONFIG_ENABLED(CONFIG_BCM2837_UART_USE_MINI)

void uart_init(void) {
#if CONFIG_ENABLED(CONFIG_BCM2837_UART_USE_MINI)
  uart_mini_init();
#else  // !CONFIG_ENABLED(CONFIG_BCM2837_UART_USE_MINI)
  uart_pl001_init();
#endif // CONFIG_ENABLED(CONFIG_BCM2837_UART_USE_MINI)
}

char uart_getc(void) {
  char c;
  irqflags_t flags;

  flags = spin_lock_irq(&uart_lock);
#if CONFIG_ENABLED(CONFIG_BCM2837_UART_USE_MINI)
  c = uart_mini_getc();
#else  // !CONFIG_ENABLED(CONFIG_BCM2837_UART_USE_MINI)
  c = uart_pl001_getc();
#endif // CONFIG_ENABLED(CONFIG_BCM2837_UART_USE_MINI)
  spin_unlock_irq(&uart_lock, flags);

  return c;
}

static void uart_putc_unlocked(const char c) {
#if CONFIG_ENABLED(CONFIG_BCM2837_UART_USE_MINI)
  uart_mini_putc(c);
#else  // !CONFIG_ENABLED(CONFIG_BCM2837_UART_USE_MINI)
  uart_pl001_putc(c);
#endif // CONFIG_ENABLED(CONFIG_BCM2837_UART_USE_MINI)
}

void uart_putc(const char c) {
  irqflags_t flags;

  flags = spin_lock_irq(&uart_lock);
  uart_putc_unlocked(c);
  spin_unlock_irq(&uart_lock, flags);
}

void uart_puts(const char *s) {
  size_t i;
  irqflags_t flags;

  flags = spin_lock_irq(&uart_lock);
  for (i = 0; s[i] != '\0'; i++) {
    uart_putc_unlocked(s[i]);
  }
  spin_unlock_irq(&uart_lock, flags);
}
