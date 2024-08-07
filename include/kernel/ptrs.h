// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_PTRS_H
#define KERNEL_PTRS_H

#include <kernel/types.h>

#define PTR_TO_ADR(ptr) ((uintptr_t)ptr)
#define REF_TO_ADR(ref) PTR_TO_ADR(&ref)
#define ADR_TO_PTR(adr) ((void *)adr)

#define container_of(ptr, type, member) ({            \
  const typeof(((type *)NULL)->member) *__mptr = ptr; \
  (type *)((uint8_t *)__mptr - offsetof(type, member));  \
})

#endif // !KERNEL_PTRS_H
