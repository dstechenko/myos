// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ARCH_AARCH64_ASM_MMU_DEFS_H
#define ARCH_AARCH64_ASM_MMU_DEFS_H

#include <kernel/util/bits.h>

#define MEMORY_TYPE_DEVICE 0x0
#define MEMORY_TYPE_DEVICE_FLAGS 0x0

#define MEMORY_TYPE_NORMAL 0x1
#define MEMORY_TYPE_NORMAL_FLAGS (BIT(2) | BIT(6))

#define MAIR_TO_VALUE(flags, index) (flags << (8 * index))
#define MAIR_VALUE                                                                                                     \
  (MAIR_TO_VALUE(MEMORY_TYPE_DEVICE_FLAGS, MEMORY_TYPE_DEVICE) |                                                       \
   MAIR_TO_VALUE(MEMORY_TYPE_NORMAL_FLAGS, MEMORY_TYPE_NORMAL))

#define MMU_TYPE_PAGE_TABLE (BIT(0) | BIT(1))
#define MMU_TYPE_PAGE (BIT(0) | BIT(1))
#define MMU_TYPE_BLOCK (BIT(0))

#define MMU_ACCESS BIT(10)
#define MMU_ACCESS_PERMISSION BIT(6)

#define MMU_NORMAL_FLAGS (MMU_TYPE_BLOCK | (MEMORY_TYPE_NORMAL << 2) | MMU_ACCESS)
#define MMU_DEVICE_FLAGS (MMU_TYPE_BLOCK | (MEMORY_TYPE_DEVICE << 2) | MMU_ACCESS)
#define MMU_PAGE_FLAGS (MMU_TYPE_PAGE | (MEMORY_TYPE_NORMAL << 2) | MMU_ACCESS | MMU_ACCESS_PERMISSION)

#endif // !ARCH_AARCH64_ASM_MMU_DEFS_H
