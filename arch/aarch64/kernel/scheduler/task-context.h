// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ARCH_AARCH64_KERNEL_SCHEDULER_TASK_CONTEXT_H
#define ARCH_AARCH64_KERNEL_SCHEDULER_TASK_CONTEXT_H

/**
 * CPU registers context for each task.
 * Accordingly to ARM calling conventions registers x0-x18 can be overwritten
 * by the called function, so the caller must not assume that the values of
 * those registers will survive after a function call.
 */
struct task_context {
  uint64_t x19;
  uint64_t x20;
  uint64_t x21;
  uint64_t x22;
  uint64_t x23;
  uint64_t x24;
  uint64_t x25;
  uint64_t x26;
  uint64_t x27;
  uint64_t x28;
  uint64_t fp;
  uint64_t sp;
  uint64_t pc;
};

#endif // !ARCH_AARCH64_KERNEL_SCHEDULER_TASK_CONTEXT_H
