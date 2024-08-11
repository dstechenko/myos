// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "cpu.h"

#include <asm/barrier.h>
#include <asm/cache.h>
#include <asm/cpu.h>

#include <kernel/assert.h>
#include <kernel/config.h>
#include <kernel/page.h>
#include <kernel/types.h>

static uintptr_t cpu_spin_table[] = {CONFIG_BOOT_CPU_SPIN_TABLE};

void cpu_init(void) {
#if CONFIG_ENABLED(CONFIG_KERNEL_SMP_ENABLED)
  ASSERT(sizeof(cpu_spin_table) / sizeof(uintptr_t) == CONFIG_BOOT_CPU_COUNT);
  for_each_cpu(index) {
    const uintptr_t release_addr = phys_to_virt(cpu_spin_table[index]);
    *((uintptr_t *)release_addr) = CONFIG_BOOT_LOAD_ADDRESS;
    cache_inv_data(release_addr);
  }
  barrier_event();
#endif  // CONFIG_ENABLED(CONFIG_KERNEL_SMP_ENABLED)
}
