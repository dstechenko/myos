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

#define MT_DEVICE_nGnRnE 0x0
#define MT_DEVICE_nGnRnE_FLAGS 0x0
#define MT_NORMAL_NC 0x1
#define MT_NORMAL_NC_FLAGS (BIT(2) | BIT(6))

#define MAIR_TO_VALUE(flags, index) (flags << (8 * index))

#define MAIR_VALUE                                                             \
  (MAIR_TO_VALUE(MT_DEVICE_nGnRnE_FLAGS, MT_DEVICE_nGnRnE) |                   \
   MAIR_TO_VALUE(MT_NORMAL_NC_FLAGS, MT_NORMAL_NC))

#define MMU_NORMAL_FLAGS (MMU_TYPE_BLOCK | (MT_NORMAL_NC << 2) | MMU_ACCESS)
#define MMU_DEVICE_FLAGS (MMU_TYPE_BLOCK | (MT_DEVICE_nGnRnE << 2) | MMU_ACCESS)
#define MMU_PAGE_FLAGS                                                         \
  (MMU_TYPE_PAGE | (MT_NORMAL_NC << 2) | MMU_ACCESS | MMU_ACCESS_PERMISSION)

#endif // !ARCH_AARCH64_ASM_MMU_DEFS_H
