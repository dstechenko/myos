// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_SPINLOCK_H
#define KERNEL_SPINLOCK_H

#include <asm/irq.h>
#include <asm/atomic.h>

#include <kernel/types.h>

TYPE(spinlock_t, atomic32_t);

irqflags_t spin_lock_irq(spinlock_t *lock);
void spin_unlock_irq(spinlock_t *lock, irqflags_t flags);

#endif // !KERNEL_SPINLOCK_H
