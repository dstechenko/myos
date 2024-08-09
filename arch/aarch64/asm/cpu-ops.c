// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/cpu.h>
#include <asm/registers.h>

#include <kernel/config.h>
#include <kernel/task.h>
#include <kernel/types.h>

uint64_t cpu_get_level(void);

void cpu_yield(void) { task_schedule(); }

enum cpu_mode cpu_get_mode(void) {
  switch (cpu_get_level()) {
    case 0:
      return CPU_MODE_USER;
    case 1:
      return CPU_MODE_KERNEL;
    default:
      return CPU_MODE_UNKNOWN;
  }
}

bool cpu_is_primary(void) { return cpu_get_core() == CONFIG_BOOT_CPU_PRIMARY_INDEX; }
