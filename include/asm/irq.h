// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_IRQ_H
#define ASM_IRQ_H
#ifndef __ASSEMBLER__

#include <kernel/types.h>

ALIAS(irqflags_t, unsigned long);

void irq_local_init(void);
void irq_local_enable(void);
irqflags_t irq_local_disable(void);
void irq_local_restore(irqflags_t flags);
bool irq_local_disabled(void);

static inline bool irq_local_enabled(void) {
  return !irq_local_disabled();
}

#endif // !__ASSEMBLER__
#endif // !ASM_IRQ_H
