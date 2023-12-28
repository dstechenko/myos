// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/cpu.h>
#include <asm/irq.h>

#include <kernel/assert.h>
#include <kernel/spinlock.h>

irqflags_t spin_lock_irq(spinlock_t *lock) {
  irqflags_t flags;

  ASSERT(lock);
  flags = local_irq_disable();

  while (true) {
    if (!atomic32_cmp_swp(&lock->value, false, true)) {
      break;
    }
    while (atomic32_get_relaxed(&lock->value)) {
      cpu_yield();
    }
  }

  return flags;
}

void spin_unlock_irq(spinlock_t *lock, irqflags_t flags) {
  ASSERT(lock);
  atomic32_set(&lock->value, false);
  local_irq_restore(flags);
}
