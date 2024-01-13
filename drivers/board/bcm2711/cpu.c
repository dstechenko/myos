// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/registers.h>
#include <drivers/cpu.h>
#include <kernel/config.h>
#include <kernel/types.h>

#define CPU_SPIN_INDEX(index) *((uint64_t *)(CONFIG_BOOT_CPU##index##_SPIN_GATE)) = CONFIG_BOOT_LOAD_ADDRESS;

void cpu_init(void) {
  /* CPU_SPIN_INDEX(0); */
  /* CPU_SPIN_INDEX(1); */
  /* CPU_SPIN_INDEX(2); */
  /* CPU_SPIN_INDEX(3); */
  /* asm volatile("dsb sy" : : : "memory"); */
  registers_test(1, CONFIG_BOOT_LOAD_ADDRESS);
  /* registers_test(2, CONFIG_BOOT_LOAD_ADDRESS); */
  /* registers_test(3, CONFIG_BOOT_LOAD_ADDRESS); */
}
