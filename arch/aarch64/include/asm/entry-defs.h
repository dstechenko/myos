// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ARCH_AARCH64_ASM_ENTRY_DEFS_H
#define ARCH_AARCH64_ASM_ENTRY_DEFS_H

#define ENTRY_STACK_FRAME_SIZE (34 * 8)

#define ENTRY_SYN_INVALID_EL1t 0
#define ENTRY_IRQ_INVALID_EL1t 1
#define ENTRY_FIQ_INVALID_EL1t 2
#define ENTRY_ERR_INVALID_EL1t 3

#define ENTRY_SYN_INVALID_EL1h 4
#define ENTRY_IRQ_INVALID_EL1h 5
#define ENTRY_FIQ_INVALID_EL1h 6
#define ENTRY_ERR_INVALID_EL1h 7

#define ENTRY_SYN_INVALID_EL0_64 8
#define ENTRY_IRQ_INVALID_EL0_64 9
#define ENTRY_FIQ_INVALID_EL0_64 10
#define ENTRY_ERR_INVALID_EL0_64 11

#define ENTRY_SYN_INVALID_EL0_32 12
#define ENTRY_IRQ_INVALID_EL0_32 13
#define ENTRY_FIQ_INVALID_EL0_32 14
#define ENTRY_ERR_INVALID_EL0_32 15

#define ENTRY_ERROR_SYN 16
#define ENTRY_ERROR_SYSCALL 17
#define ENTRY_ERROR_DATA_ABORT 18

#endif  // !ARCH_AARCH64_ASM_ENTRY_DEFS_H
