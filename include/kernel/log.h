// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_LOG_H
#define KERNEL_LOG_H

#include <stdint.h>

#include <kernel/config.h>

#define LOG_ERROR 0
#define LOG_INFO 1
#define LOG_DEBUG 2

#define log_error(line) log(LOG_ERROR, line)
#define log_info(line) log(LOG_INFO, line)
#define log_debug(line) log(LOG_DEBUG, line)
#define log(level, line) log_impl(level, line)

int log_init();
void log_impl(uint8_t, const char *line);

#endif // !KERNEL_LOG_H
