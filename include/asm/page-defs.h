// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_PAGE_DEFS_H
#define ASM_PAGE_DEFS_H

#include <kernel/core/config.h>

#define PAGE_SHIFT CONFIG_PAGE_SHIFT
#define PAGE_SIZE (BIT(PAGE_SHIFT))
#define PAGE_MASK (~(PAGE_SIZE - 1))

#define TABLE_SHIFT CONFIG_TABLE_SHIFT

#define SECTION_SHIFT (PAGE_SHIFT + TABLE_SHIFT)
#define SECTION_SIZE (BIT(SECTION_SHIFT))
#define SECTION_MASK (~(SECTION_SIZE - 1))

#endif // !ASM_PAGE_DEFS_H
