// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_REGISTERS_H
#define ASM_REGISTERS_H
#ifndef __ASSEMBLER__

int registers_get_priv(void);
uintptr_t registers_get_page_table(void);
void registers_set_page_table(uintptr_t table);

#endif // !__ASSEMBLER__
#endif // !ASM_REGISTERS_H
