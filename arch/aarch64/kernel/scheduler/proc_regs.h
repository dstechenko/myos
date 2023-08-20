// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ARCH_AARCH64_KERNEL_SCHEDULER_PROC_REGS_H
#define ARCH_AARCH64_KERNEL_SCHEDULER_PROC_REGS_H

#include <stdint.h>

struct proc_regs {
  uint64_t regs[31];
  uint64_t sp;
  uint64_t pc;
  uint64_t st;
};

#endif // !ARCH_AARCH64_KERNEL_SCHEDULER_PROC_REGS_H
