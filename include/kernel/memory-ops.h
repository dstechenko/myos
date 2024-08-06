// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_MEMORY_OPS_H
#define KERNEL_MEMORY_OPS_H

#include <kernel/types.h>

void *memcpy(void *dst, const void *src, size_t cnt);
void *memset(void *dst, uint8_t val, size_t cnt);
void *memzero(void *dst, size_t cnt);

#endif // !KERNEL_MEMORY_OPS_H
