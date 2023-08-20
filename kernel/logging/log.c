// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/logging/log.h>

#include <stdarg.h>
#include <stddef.h>

#include <kernel/config.h>
#include <kernel/util/error.h>

#if CONFIG_ENABLED(CONFIG_UART_ON)
#include <drivers/uart.h>
#endif // CONFIG_ENABLED(CONFIG_UART_ON)

static void (*log_putc)(char) = NULL;

static void (*log_puts)(const char *) = NULL;

static const char *log_level_to_string(const uint8_t level) {
  switch (level) {
  case ERROR:
    return "[ERROR]";
  case INFO:
    return " [INFO]";
  case DEBUG:
    return "[DEBUG]";
  }
  // TODO: should assert here and fail?
  return "[ERROR]";
}

static void log_negative(const int num)
{
  if (num < 0)
    log_putc('-');
}

static void log_convert(int num, const uint8_t base) {
  static const char digits[] = "0123456789ABCDEF";
  char buffer[20];
  char *cursor;

  // TODO: add asserts here...

  if (num < 0)
    num = -num;

  cursor = &buffer[sizeof(buffer) - 1];
  *cursor = '\0';

  do {
    *(--cursor) = digits[num % base];
    num /= base;
  } while (num != 0 && cursor != &buffer[0]);

  log_puts(cursor);
}

static void log_format(va_list *args, const char format) {
  int arg;

  // TODO: add asserts here...

  switch (format) {
  case 'c':
    arg = va_arg(*args, int);
    log_putc((char)arg);
    break;
  case 'd':
    arg = va_arg(*args, int);
    log_negative(arg);
    log_convert(arg, 10);
    break;
  case 'o':
    arg = va_arg(*args, int);
    log_negative(arg);
    log_putc('0');
    log_convert(arg, 8);
    break;
  case 's':
    log_puts(va_arg(*args, const char *));
    break;
  case 'x':
    arg = va_arg(*args, int);
    log_negative(arg);
    log_puts("0x");
    log_convert(arg, 16);
    break;
  default:
    // TODO: add asserts here too?
    break;
  }
}

int log_init() {
  int err = -EINVAL;
#if CONFIG_ENABLED(CONFIG_UART_ON)
  err = 0;
  uart_init();
  log_putc = uart_putc;
  log_puts = uart_puts;
#endif // CONFIG_ENABLED(CONFIG_UART_ON)
  return err;
}

void log(const uint8_t level, const char *format, ...) {
  va_list args;
  const char *cursor;

  // TODO: add assert here...
  // TODO: add timestamps to logs...

  if (CONFIG_LOG_LEVEL < level)
    return;

  log_puts(log_level_to_string(level));
  log_puts(" ");
  va_start(args, format);
  for (cursor = format; *cursor != '\0'; cursor++) {
    if (*cursor == '%') {
      cursor++;
      log_format(&args, *cursor);
    } else {
      log_putc(*cursor);
    }
  }
  va_end(args);
  log_puts("\r\n");
}
