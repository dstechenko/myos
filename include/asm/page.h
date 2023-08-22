// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_PAGE_H
#define ASM_PAGE_H

#include <asm/page-defs.h>
#include <kernel/util/bits.h>

#define SECTION_SHIFT (PAGE_SHIFT + TABLE_SHIFT)

#define PAGE_SIZE (BIT(PAGE_SHIFT))
#define PAGE_MASK (~(PAGE_SIZE - 1))

#define SECTION_SIZE (BIT(SECTION_SHIFT))
#define SECTION_MASK (~(SECTION_SIZE - 1))

#define PTRS_PER_TABLE (BIT(TABLE_SHIFT))

#define PGD_SHIFT (PAGE_SHIFT + 3 * TABLE_SHIFT)
#define PUD_SHIFT (PAGE_SHIFT + 2 * TABLE_SHIFT)
#define PMD_SHIFT (PAGE_SHIFT + 1 * TABLE_SHIFT)

#define PG_DIR_SIZE (3 * PAGE_SIZE)

#ifndef __ASSEMBLER__
#endif // !__ASSEMBLER__

#endif // !ASM_PAGE_H
