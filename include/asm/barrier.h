// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_BARRIER_H
#define ASM_BARRIER_H
#ifndef __ASSEMBLER__

void barrier_data_mem(void);
void barrier_data_sync(void);
void barrier_inst_sync(void);
void barrier_event(void);

#endif // !__ASSEMBLER__
#endif // !ASM_BARRIER_H
