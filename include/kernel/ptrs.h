// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_PTRS_H
#define KERNEL_PTRS_H

#include <asm/memory-defs.h>

#define PTR_TO_ADR(ptr) ((uintptr_t)ptr)
#define REF_TO_ADR(ref) PTR_TO_ADR(&ref)
#define ADR_TO_PTR(adr) ((void *)adr)

#endif // !KERNEL_PTRS_H
