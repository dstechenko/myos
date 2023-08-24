// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_PAGE_H
#define ASM_PAGE_H

#include <asm/page-defs.h>
#include <kernel/util/bits.h>

#define PAGE_ENTRIES_PER_TABLE (BIT(TABLE_SHIFT))

#define PAGE_GLOBAL_DIRECTORY_SIZE (3 * PAGE_SIZE)

#define PAGE_GLOBAL_DIRECTORY_SHIFT (PAGE_SHIFT + 3 * TABLE_SHIFT)
#define PAGE_UPPER_DIRECTORY_SHIFT (PAGE_SHIFT + 2 * TABLE_SHIFT)
#define PAGE_MIDDLE_DIRECTORY_SHIFT (PAGE_SHIFT + 1 * TABLE_SHIFT)

#ifndef __ASSEMBLER__
#endif // !__ASSEMBLER__

#endif // !ASM_PAGE_H
