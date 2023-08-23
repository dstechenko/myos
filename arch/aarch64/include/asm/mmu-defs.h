// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ARCH_AARCH64_ASM_MMU_DEFS_H
#define ARCH_AARCH64_ASM_MMU_DEFS_H

#include <kernel/util/bits.h>

#define MMU_TYPE_PAGE_TABLE (BIT(0) | BIT(1))
#define MMU_TYPE_PAGE (BIT(0) | BIT(1))
#define MMU_TYPE_BLOCK (BIT(0))

#define MMU_ACCESS (BIT(10))
#define MMU_ACCESS_PERMISSION (BIT(6))

#endif // !ARCH_AARCH64_ASM_MMU_DEFS_H
