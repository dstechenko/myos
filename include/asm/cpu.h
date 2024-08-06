// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_CPU_H
#define ASM_CPU_H
#ifndef __ASSEMBLER__

#include <kernel/types.h>

enum cpu_mode {
  CPU_MODE_UNKNOWN,
  CPU_MODE_KERNEL,
  CPU_MODE_USER,
};

void cpu_yield(void);

enum cpu_mode cpu_get_mode(void);
uint32_t cpu_get_core(void);
bool cpu_is_primary(void);

void cpu_set_user_pt(uintptr_t pt);
uintptr_t cpu_get_user_pt(void);

void cpu_set_kernel_pt(uintptr_t pt);
uintptr_t cpu_get_kernel_pt(void);

#endif // !__ASSEMBLER__
#endif // !ASM_CPU_H
