// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_OPS_H
#define KERNEL_OPS_H

#include <stddef.h>
#include <stdint.h>

void *memcpy(void *dst, const void *src, size_t cnt);
void *memset(void *dst, uint8_t val, size_t cnt);
void *memzero(void *dst, size_t cnt);

#endif // !KERNEL_OPS_H
