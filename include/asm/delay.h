// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_DELAY_H
#define ASM_DELAY_H
#ifndef __ASSEMBLER__

#include <stdint.h>

void delay_nop(void);
void delay_cycles(uint64_t cycles);
void delay_sec(uint64_t sec);
void delay_msec(uint64_t msec);
void delay_nsec(uint64_t nsec);

#endif // !__ASSEMBLER__
#endif // !ASM_DELAY_H
