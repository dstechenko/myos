// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/log.h>

#include <stddef.h>

#include <kernel/config.h>
#include <kernel/error.h>

#if CONFIG_ENABLED(CONFIG_UART_ON)
#include <drivers/uart.h>
#endif // CONFIG_ENABLED(CONFIG_UART_ON)

static void (*log_driver_impl)(const char *) = NULL;

static const char *log_level_to_string(uint8_t level)
{
	switch (level) {
	case LOG_ERROR:
		return "ERROR";
	case LOG_INFO:
		return "INFO";
	case LOG_DEBUG:
		return "DEBUG";
	}
	// TODO: should assert here and fail?
	return "ERROR";
}

int log_init()
{
	int err = -EINVAL;
#if CONFIG_ENABLED(CONFIG_UART_ON)
	err = 0;
	uart_init();
	log_driver_impl = uart_puts;
#endif // CONFIG_ENABLED(CONFIG_UART_ON)
	return err;
}

void log_impl(uint8_t level, const char *line)
{
	// TODO: add assert here...
	log_driver_impl("[");
	log_driver_impl(log_level_to_string(level));
	log_driver_impl("] ");
	log_driver_impl(line);
	log_driver_impl("\r\n");
}
