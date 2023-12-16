// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_REGISTERS_H
#define ASM_REGISTERS_H
#ifndef __ASSEMBLER__

#include <stdint.h>

int registers_get_priv(void);
int registers_get_core(void);

void registers_set_user_page_table(uintptr_t table);
uintptr_t registers_get_user_page_table(void);

void registers_set_kernel_page_table(uintptr_t table);
uintptr_t registers_get_kernel_page_table(void);

#endif // !__ASSEMBLER__
#endif // !ASM_REGISTERS_H
