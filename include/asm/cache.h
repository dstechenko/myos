// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_CACHE_H
#define ASM_CACHE_H
#ifndef __ASSEMBLER__

#include <kernel/types.h>

void cache_inv_data(uintptr_t ptr);
void cache_inv_inst(uintptr_t ptr);
void cache_inv_tlbs(void);

#endif // !__ASSEMBLER__
#endif // !ASM_CACHE_H
