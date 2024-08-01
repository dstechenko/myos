// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_REGISTERS_H
#define ASM_REGISTERS_H
#ifndef __ASSEMBLER__

#include <kernel/types.h>

uint32_t registers_get_priv(void);
uint32_t registers_get_core(void);

void registers_set_user_page_table(uintptr_t table);
uintptr_t registers_get_user_page_table(void);

void registers_set_kernel_page_table(uintptr_t table);
uintptr_t registers_get_kernel_page_table(void);

void registers_test(uint64_t core, uintptr_t start);
void registers_enable_mmu(void);

void cache_invalidate(uintptr_t va);
void cache_barrier(void);

#endif // !__ASSEMBLER__
#endif // !ASM_REGISTERS_H
