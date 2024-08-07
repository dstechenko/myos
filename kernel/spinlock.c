// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/cpu.h>
#include <asm/irq.h>

#include <kernel/assert.h>
#include <kernel/spinlock.h>

void spin_lock_init(spinlock_t *lock) {
  ASSERT(lock);
  atomic32_set(&lock->value, false);
}

irqflags_t spin_lock_irq(spinlock_t *lock) {
  irqflags_t flags;

  ASSERT(lock);
  flags = irq_local_disable();

  while (true) {
    if (!atomic32_cmp_swp(&lock->value, false, true)) {
      break;
    }
    while (atomic32_get_relaxed(&lock->value)) {
      // TODO(dstechenko): do some yield/noop logic here
    }
  }

  return flags;
}

void spin_unlock_irq(spinlock_t *lock, const irqflags_t flags) {
  spin_lock_init(lock);
  irq_local_restore(flags);
}
