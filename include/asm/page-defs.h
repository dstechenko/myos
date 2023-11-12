// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_PAGE_DEFS_H
#define ASM_PAGE_DEFS_H

#include <kernel/config.h>
#include <kernel/bits.h>

#define PAGE_SHIFT CONFIG_PAGE_SHIFT
#define PAGE_SIZE BIT(PAGE_SHIFT)
#define PAGE_MASK ~(PAGE_SIZE - 1)

#define TABLE_SHIFT CONFIG_TABLE_SHIFT

#define SECTION_SHIFT (PAGE_SHIFT + TABLE_SHIFT)
#define SECTION_SIZE BIT(SECTION_SHIFT)
#define SECTION_MASK ~(SECTION_SIZE - 1)

#define PAGES_PER_TABLE BIT(TABLE_SHIFT)

#define PGD_SHIFT (PAGE_SHIFT + 3 * TABLE_SHIFT)
#define PUD_SHIFT (PAGE_SHIFT + 2 * TABLE_SHIFT)
#define PMD_SHIFT (PAGE_SHIFT + 1 * TABLE_SHIFT)

#endif // !ASM_PAGE_DEFS_H
