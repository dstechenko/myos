// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/memory-defs.h>
#include <asm/mmu-defs.h>
#include <asm/page-defs.h>
#include <asm/registers-defs.h>

// To keep this in the first portion of the binary.
.section ".text.boot"

// Make _start global. Need this to get execution transferred from armstub8.
.globl BOOT_ENTRY_POINT_LABEL

BOOT_ENTRY_POINT_LABEL:
boot_start:
  // Check our current exception level.
  // Depending on the boot loader we could be in EL2 or EL3.
  mrs x0, currentel
  lsr x0, x0, #2
  cmp x0, #3
  bne boot_init_el2

boot_init_el3:
  // Set EL3 secure configurations and switch to EL2.
  ldr x0, =SCR_EL3_VALUE
  msr scr_el3, x0
  ldr x0, =SPSR_EL2h_VALUE
  msr spsr_el3, x0
  ldr x0, =boot_init_el2
  msr elr_el3, x0
  eret

boot_init_el2:
  // Set hypervisor and system control configurations and
  // switch to EL1 for kernel entry.
  // Disabling MMU, IRQs and data/instruction caching.
  ldr x0, =SCTLR_EL1_VALUE
  msr sctlr_el1, x0
  ldr x0, =HCR_EL2_VALUE
  msr hcr_el2, x0
  ldr x0, =SPSR_EL1h_VALUE
  msr spsr_el2, x0
  ldr x0, =boot_init_stack
  msr elr_el2, x0
  eret

boot_init_stack:
  // Set stack before we jump into kernel.
  ldr x0, =boot_start
  mov sp, x0

  // Move stack separately for each core.
  mrs x0, mpidr_el1
  and x0, x0, #0xFF
  mov x1, #PAGE_SIZE
  mul x2, x0, x1
  sub sp, sp, x2

  // Skip page table creation for non-primary core.
  cbnz x0, boot_init_page_tables

  // Set up initial kernel/device pages.
  bl boot_create_page_tables

boot_init_page_tables:
  // Set page tables from the created variables
  ldr x0, =boot_user_pgd
  ldr x1, [x0]
  msr ttbr0_el1, x1
  ldr x0, =boot_kernel_pgd
  ldr x1, [x0]
  msr ttbr1_el1, x1

  // Grab the offset before we enable MMU and move to virtual.
  // Also move the stack pointer for the init task into virtual.
  ldr x0, =VIRTUAL_MEMORY_OFFSET
  ldr x1, =boot_start
  add x1, x1, x0
  mov sp, x1

  // Move stack separately for each core.
  mrs x3, mpidr_el1
  and x3, x3, #0xFF
  mov x4, #PAGE_SIZE
  mul x3, x3, x4
  sub sp, sp, x3

  ldr x1, =section_kernel_entry_point;
  add x1, x1, x0

  // Enable MMU via system control register. No need to flush.
  ldr x0, =TCR_EL1_VALUE
  msr tcr_el1, x0
  ldr x0, =MAIR_EL1_VALUE
  msr mair_el1, x0
  ldr x0, =SCTLR_EL1_MMU_VALUE
  msr sctlr_el1, x0

boot_jump_kernel:
  // Jump to the kernel entry point. This should not return.
  br x1
