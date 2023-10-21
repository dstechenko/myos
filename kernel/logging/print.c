// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/logging/print.h>

#include <stddef.h>
#include <stdint.h>

#include <kernel/core/config.h>
#include <kernel/core/error.h>
#include <kernel/util/assert.h>
#include <kernel/util/math.h>

#if CONFIG_ENABLED(CONFIG_BCM2837_UART_ON)
#include <drivers/uart.h>
#endif // CONFIG_ENABLED(CONFIG_BCM2837_UART_ON)

#define PRINT_BUFFER_SIZE 30
#define PRINT_BASE_OCT 8
#define PRINT_BASE_DEC 10
#define PRINT_BASE_HEX 16

static void (*print_putc)(char) = NULL;
static void (*print_puts)(const char *) = NULL;

static void print_convert(uint64_t num, const uint8_t base) {
  static const char digits[] = "0123456789ABCDEF";
  char buffer[PRINT_BUFFER_SIZE];
  char *cursor;

  cursor = &buffer[sizeof(buffer) - 1];
  *cursor = '\0';

  do {
    *(--cursor) = digits[num % base];
    num /= base;
  } while (num != 0 && cursor != &buffer[0]);

  print_puts(cursor);
}

static void print_format_digits(va_list *args, const char format) {
  int var_d;
  unsigned int var_u;

  ASSERT(args);
  ASSERT(format);

  switch (format) {
  case 'd':
    var_d = va_arg(*args, int);
    if (var_d < 0)
      print_putc('-');
    print_convert(abs(var_d), PRINT_BASE_DEC);
    break;
  case 'u':
    var_u = va_arg(*args, unsigned int);
    print_convert(var_u, PRINT_BASE_DEC);
    break;
  case 'o':
    var_u = va_arg(*args, unsigned int);
    print_putc('0');
    print_convert(var_u, PRINT_BASE_OCT);
    break;
  case 'x':
    var_u = va_arg(*args, unsigned int);
    print_puts("0x");
    print_convert(var_u, PRINT_BASE_HEX);
    break;
  default:
    ABORT();
  }
}

static void print_format_long_digits(va_list *args, const char format) {
  long int var_d;
  long unsigned int var_u;

  ASSERT(args);
  ASSERT(format);

  switch (format) {
  case 'd':
    var_d = va_arg(*args, long int);
    if (var_d < 0)
      print_putc('-');
    print_convert(abs(var_d), PRINT_BASE_DEC);
    break;
  case 'u':
    var_u = va_arg(*args, long unsigned int);
    print_convert(var_u, PRINT_BASE_DEC);
    break;
  case 'o':
    var_u = va_arg(*args, long unsigned int);
    print_putc('0');
    print_convert(var_u, PRINT_BASE_OCT);
    break;
  case 'x':
    var_u = va_arg(*args, long unsigned int);
    print_puts("0x");
    print_convert(var_u, PRINT_BASE_HEX);
    break;
  default:
    ABORT();
  }
}

static void print_format(va_list *args, const char **cursor) {
  ASSERT(args);
  ASSERT(cursor);

  switch (**cursor) {
  case 'c':
    print_putc((char)va_arg(*args, int));
    break;
  case 's':
    print_puts(va_arg(*args, const char *));
    break;
  case 'l':
    (*cursor)++;
    print_format_long_digits(args, **cursor);
    break;
  default:
    print_format_digits(args, **cursor);
  }
}

int print_init(void) {
  int err = -EINVAL;
#if CONFIG_ENABLED(CONFIG_BCM2837_UART_ON)
  err = 0;
  uart_init();
  print_putc = uart_putc;
  print_puts = uart_puts;
#endif // CONFIG_ENABLED(CONFIG_BCM2837_UART_ON)
  return err;
}

// TODO: on hw seems like lines not getting fully sent
void print(const char *format, ...) {
  va_list args;

  ASSERT(format);

  va_start(args, format);
  print_args(format, &args);
  va_end(args);
}

void print_args(const char *format, va_list *args) {
  const char *cursor;

  ASSERT(format);
  ASSERT(args);

  for (cursor = format; *cursor != '\0'; cursor++) {
    if (*cursor == '%') {
      cursor++;
      print_format(args, &cursor);
    } else {
      print_putc(*cursor);
    }
  }
}
