// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_PRINT_H
#define KERNEL_PRINT_H

#include <stdarg.h>

int print_init(void);
void print(const char *format, ...);
void print_args(const char *format, va_list *args);

#endif // !KERNEL_PRINT_H
