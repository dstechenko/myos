// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_LOG_H
#define KERNEL_LOG_H

#include <stdint.h>

#include <kernel/config.h>

#define LOG_ERROR 0
#define LOG_INFO 1
#define LOG_DEBUG 2

#if (CONFIG_LOG_LEVEL >= LOG_ERROR)
#define log_error(format, ...) log(LOG_ERROR, format, ##__VA_ARGS__)
#else // (CONFIG_LOG_LEVEL >= LOG_ERROR)
#define log_error(format, ...)                                                 \
	do {                                                                   \
	} while (false)
#endif // !(CONFIG_LOG_LEVEL >= LOG_ERROR)

#if (CONFIG_LOG_LEVEL >= LOG_INFO)
#define log_info(format, ...) log(LOG_INFO, format, ##__VA_ARGS__)
#else // (CONFIG_LOG_LEVEL >= LOG_INFO)
#define log_info(format, ...)                                                  \
	do {                                                                   \
	} while (false)
#endif // !(CONFIG_LOG_LEVEL >= LOG_INFO)

#if (CONFIG_LOG_LEVEL >= LOG_DEBUG)
#define log_debug(format, ...) log(LOG_DEBUG, format, ##__VA_ARGS__)
#else // (CONFIG_LOG_LEVEL >= LOG_DEBUG)
#define log_debug(format, ...)                                                 \
	do {                                                                   \
	} while (false)
#endif // !(CONFIG_LOG_LEVEL >= LOG_DEBUG)

int log_init();
void log(uint8_t level, const char *format, ...);

#endif // !KERNEL_LOG_H
