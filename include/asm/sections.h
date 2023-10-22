// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_SECTIONS_DEFS_H
#define ASM_SECTIONS_DEFS_H
#ifndef __ASSEMBLER__

#include <stdint.h>

#define SECTION_LABEL(label) void label(void)
#define SECTION_ADR(label) ((uintptr_t)label)

void sections_debug(void);

#endif // !__ASSEMBLER__
#endif // !ASM_SECTIONS_DEFS_H