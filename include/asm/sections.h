// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_SECTIONS_DEFS_H
#define ASM_SECTIONS_DEFS_H
#ifndef __ASSEMBLER__

#include <kernel/types.h>

#define SECTIONS_LABEL(name) \
  void name(void);

#define SECTIONS(label) \
  SECTIONS_LABEL(label ## _start); \
  SECTIONS_LABEL(label ## _end);

#define SECTIONS_START(label) ((uintptr_t)(label ## _start))
#define SECTIONS_END(label) ((uintptr_t)(label ## _end))
#define SECTIONS_LENGTH(label) ((size_t)(SECTIONS_END(label) - SECTIONS_START(label)))

void sections_init(void);
void sections_debug(void);

#endif // !__ASSEMBLER__
#endif // !ASM_SECTIONS_DEFS_H
