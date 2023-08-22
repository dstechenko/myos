// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_IRQ_H
#define ASM_IRQ_H
#ifndef __ASSEMBLER__

#include <stdint.h>

#include <kernel/util/bool.h>

void irq_init(void);
void irq_enable(void);
bool irq_enabled(void);
void irq_disable(void);
bool irq_disabled(void);
void irq_save(uint64_t *flags);
void irq_restore(uint64_t *flags);

#endif // !__ASSEMBLER__
#endif // !ASM_IRQ_H
