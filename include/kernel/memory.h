// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_MEMORY_H
#define KERNEL_MEMORY_H

#include <kernel/bits.h>
#include <kernel/types.h>
#include <kernel/page.h>

void *memory_alloc(size_t size, uint8_t flags);
void *memory_zalloc(size_t size, uint8_t flags);
void memory_free(const void *ptr);

#endif // !KERNEL_MEMORY_H
