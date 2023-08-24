// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ARCH_AARCH64_ASM_PROC_REGS_H
#define ARCH_AARCH64_ASM_PROC_REGS_H
#ifndef __ASSEMBLER__

#include <stdint.h>

#include <asm/system-levels.h>
#include <kernel/util/assert.h>

struct proc_regs {
  uint64_t regs[31];
  uint64_t sp;
  uint64_t pc;
  uint64_t ps;
};

STATIC_ASSERT(sizeof(struct proc_regs) == ENTRY_STACK_FRAME_SIZE, proc_regs_size);

#endif // !__ASSEMBLER__
#endif // !ARCH_AARCH64_ASM_PROC_REGS_H
