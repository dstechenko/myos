// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_LOG_H
#define KERNEL_LOG_H

#include <stdint.h>

#include <kernel/config.h>

#define ERROR 0
#define INFO 1
#define DEBUG 2

#if (CONFIG_LOG_LEVEL >= LOG_ERROR)
#define LOG_ERROR(format, ...) log(ERROR, format, ##__VA_ARGS__)
#else // (CONFIG_LOG_LEVEL >= LOG_ERROR)
#define LOG_ERROR(format, ...) do { } while (false)
#endif // !(CONFIG_LOG_LEVEL >= LOG_ERROR)

#if (CONFIG_LOG_LEVEL >= LOG_INFO)
#define LOG_INFO(format, ...) log(INFO, format, ##__VA_ARGS__)
#else // (CONFIG_LOG_LEVEL >= LOG_INFO)
#define LOG_INFO(format, ...) do { } while (false)
#endif // !(CONFIG_LOG_LEVEL >= LOG_INFO)

#if (CONFIG_LOG_LEVEL >= LOG_DEBUG)
#define LOG_DEBUG(format, ...) log(DEBUG, format, ##__VA_ARGS__)
#else // (CONFIG_LOG_LEVEL >= LOG_DEBUG)
#define LOG_DEBUG(format, ...) do { } while (false)
#endif // !(CONFIG_LOG_LEVEL >= LOG_DEBUG)

void log(uint8_t level, const char *format, ...);

#endif // !KERNEL_LOG_H
