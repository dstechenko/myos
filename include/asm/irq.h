// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_IRQ_H
#define ASM_IRQ_H
#ifndef __ASSEMBLER__

#include <stdint.h>

#include <uapi/bool.h>

void local_irq_init(void);

void local_irq_enable(void);
void local_irq_disable(void);

bool local_irq_enabled(void);
bool local_irq_disabled(void);

void local_irq_save(uint64_t *flags);
void local_irq_restore(uint64_t *flags);

#endif // !__ASSEMBLER__
#endif // !ASM_IRQ_H
