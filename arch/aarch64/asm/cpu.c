// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/barrier.h>
#include <asm/cache.h>
#include <asm/cpu.h>
#include <asm/registers.h>

#include <kernel/config.h>
#include <kernel/task.h>
#include <kernel/types.h>

uint32_t cpu_get_level(void) {
  const uint32_t el = registers_get_pstate_el();
  return REGISTERS_PSTATE_SELECT_EL(el);
}

uint32_t cpu_get_core(void) {
  const uint32_t mpidr = registers_get_mpidr_el1();
  return REGISTERS_MPIDR_SELECT_AFF0(mpidr);
}

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

void cpu_set_user_pt(const uintptr_t pt) {
  barrier_data_sync();
  registers_set_ttbr0_el1(pt);
  barrier_inst_sync();
  cache_inv_tlbs();
  barrier_data_sync();
  barrier_inst_sync();
}

uintptr_t cpu_get_user_pt(void) { return registers_get_ttbr0_el1(); }

void cpu_set_kernel_pt(const uintptr_t pt) {
  barrier_data_sync();
  registers_set_ttbr1_el1(pt);
  barrier_inst_sync();
  cache_inv_tlbs();
  barrier_data_sync();
  barrier_inst_sync();
}

uintptr_t cpu_get_kernel_pt(void) { return registers_get_ttbr1_el1(); }
