// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_SECTIONS_DEFS_H
#define ASM_SECTIONS_DEFS_H
#ifndef __ASSEMBLER__

#define SECTION_LABEL(label) void label(void)
#define SECTION_ADDR(label) ((uintptr_t)label)

#endif // !__ASSEMBLER__
#endif // !ASM_SECTIONS_DEFS_H
