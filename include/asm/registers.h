// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_REGISTERS_H
#define ASM_REGISTERS_H
#ifndef __ASSEMBLER__

int registers_get_priv(void);
void registers_set_user_page_table(uintptr_t table);
void registers_set_kernel_page_table(uintptr_t table);

#endif // !__ASSEMBLER__
#endif // !ASM_REGISTERS_H
