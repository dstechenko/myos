// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_BARRIER_H
#define ASM_BARRIER_H
#ifndef __ASSEMBLER__

void barrier_compiler(void);
void barrier_data_memory(void);
void barrier_data_sync(void);
void barrier_instruction_sync(void);

#endif // !__ASSEMBLER__
#endif // !ASM_BARRIER_H
