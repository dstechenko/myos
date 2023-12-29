// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_ABORT_H
#define ASM_ABORT_H
#ifndef __ASSEMBLER__

#include <kernel/task.h>

void abort_and_wait(void);

static inline void abort(void) {
  task_preempt_disable();
  abort_and_wait();
}

#endif // !__ASSEMBLER__
#endif // !ASM_ABORT_H
