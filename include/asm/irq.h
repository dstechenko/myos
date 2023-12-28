// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_IRQ_H
#define ASM_IRQ_H
#ifndef __ASSEMBLER__

#include <kernel/types.h>

ALIAS(irqflags_t, unsigned long);

void local_irq_init(void);
void local_irq_enable(void);
irqflags_t local_irq_disable(void);
void local_irq_restore(irqflags_t flags);
bool local_irq_enabled(void);

static inline bool local_irq_disabled(void) {
  return !local_irq_enabled();
}

#endif // !__ASSEMBLER__
#endif // !ASM_IRQ_H
