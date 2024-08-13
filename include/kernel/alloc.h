// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_ALLOCATOR_H
#define KERNEL_ALLOCATOR_H

#include <kernel/bits.h>
#include <kernel/types.h>

#define ALLOC_KERNEL BIT(0)
#define ALLOC_USER BIT(1)

void *alloc(size_t size, uint8_t flags);
void *alloc_zero(size_t size, uint8_t flags);
void alloc_free(const void *ptr);

#endif // !KERNEL_ALLOCATOR_H
