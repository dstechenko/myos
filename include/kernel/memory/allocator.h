// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_ALLOCATOR_H
#define KERNEL_ALLOCATOR_H

#include <stddef.h>
#include <stdint.h>

#define PAGE_SIZE 4096

#define ALLOC_NONE 0

void *alloc(size_t size, uint8_t flags);
void *zalloc(size_t size, uint8_t flags);
void free(const void *obj);

#endif // !KERNEL_ALLOCATOR_H
