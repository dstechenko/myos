// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/memory-defs.h>
#include <asm/mmu-defs.h>
#include <asm/page-defs.h>
#include <asm/registers-defs.h>

#include <kernel/core/config.h>

// To keep this in the first portion of the binary.
.section ".text.boot"

// Make _start global. Need this to get execution transferred from armstub8.
.globl BOOT_ENTRY_POINT_LABEL

.macro boot_create_page_global_directory table, vaddr, aux0, aux1
  boot_create_page_table_entry \table, \vaddr, PGD_SHIFT, \aux0, \aux1
  boot_create_page_table_entry \table, \vaddr, PUD_SHIFT, \aux0, \aux1
.endm

.macro boot_create_page_table_entry table, vaddr, shift, aux0, aux1
  lsr \aux0, \vaddr, #\shift
  and \aux0, \aux0, #PAGES_PER_TABLE - 1
  add \aux1, \table, #PAGE_SIZE
  orr \aux1, \aux1, #MMU_TYPE_PAGE_TABLE
  str \aux1, [\table, \aux0, lsl #3]
  add \table, \table, #PAGE_SIZE
.endm

.macro boot_create_page_block_mapping table, paddr, start, end, flags, aux0
  lsr \start, \start, #SECTION_SHIFT
  and \start, \start, #PAGES_PER_TABLE - 1
  lsr \end, \end, #SECTION_SHIFT
  and \end, \end, #PAGES_PER_TABLE - 1
  lsr \paddr, \paddr, #SECTION_SHIFT
  mov \aux0, #\flags
  orr \paddr, \aux0, \paddr, lsl #SECTION_SHIFT
9999:
  str \paddr, [\table, \start, lsl #3]
  add \start, \start, #1
  add \paddr, \paddr, #SECTION_SIZE
  cmp \start, \end
  bls 9999b
.endm

BOOT_ENTRY_POINT_LABEL:
boot_start:
  // Entry point for the kernel.
  // We need to halt all of the non-primary CPUs since they
  // all might execute the same code. Depends on the firmware.
  // Check a multiprocessor affinity register to id it (0 is primary core).
  mrs x0, mpidr_el1
  and x0, x0, #0xFF
  cbnz x0, boot_halt_core

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
  adr x0, boot_init_el2
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
  adr x0, boot_init_kernel
  msr elr_el2, x0
  eret

boot_init_kernel:
  // Set stack before we jump into kernel.
  ldr x0, =boot_start
  mov sp, x0

  // Also zero-out bss section to prepare kernel.
  ldr x0, =section_bss_start
  ldr x1, =(section_bss_end - 1)
  sub x1, x1, x0
  bl memzero

  // Set up initial kernel/device pages.
  bl boot_create_page_tables

  // Point identity boot level translation table base register.
  adrp x0, section_pgd_boot_start
  msr ttbr0_el1, x0

  // Point kernel level translation table base register.
  adrp x0, section_pgd_kernel_start
  msr ttbr1_el1, x0

  // Configure translation control register (pages size etc).
  ldr x0, =(TCR_EL1_VALUE)
  msr tcr_el1, x0
  isb

  // Set up memory attribute indirection register (additional attributes for translation).
  ldr x0, =(MAIR_VALUE)
  msr mair_el1, x0

  // Grab the offset before we enable MMU and move to virtual.
  // Also move the stack pointer for the init task into virtual.
  ldr x1, =VIRTUAL_MEMORY_START
  ldr x2, =0x60000
  add x2, x2, x1
  mov sp, x2
  ldr x2, =kernel_start
  add x2, x2, x1

  // Enable MMU via system control register.
  ldr x0, =(SCTLR_EL1_MMU_VALUE)
  msr sctlr_el1, x0
  isb

boot_jump_kernel:
  // Jump to the kernel entry point. This should not return.
  br x2

boot_halt_core:
  // For failsafe, halt this core.
  // We should not reach here, but if we do - we cannot recover.
  wfe
  b boot_halt_core

boot_create_page_tables:
  // Save link register to return after.
  mov x29, x30

  // Prepare the pages before mapping (zero out).
  ldr x0, =section_pgd_start
  ldr x1, =(section_pgd_end - 1)
  sub x1, x1, x0
  bl memzero

  // Create boot page global directory entries (identity).
  ldr x0, =section_pgd_boot_start
  ldr x1, =PHYSICAL_MEMORY_START
  boot_create_page_global_directory x0, x1, x2, x3

  // Map boot sections (identity).
  ldr x1, =PHYSICAL_MEMORY_START
  ldr x2, =PHYSICAL_MEMORY_START
  ldr x3, =(PHYSICAL_DEVICE_MEMORY_START - SECTION_SIZE)
  boot_create_page_block_mapping x0, x1, x2, x3, MMU_NORMAL_FLAGS, x4

  // Create kernel/device page global directory entries (virtual).
  ldr x0, =section_pgd_kernel_start
  ldr x1, =VIRTUAL_MEMORY_START
  boot_create_page_global_directory x0, x1, x2, x3

  // Map kernel sections (virtual).
  ldr x1, =PHYSICAL_MEMORY_START
  ldr x2, =VIRTUAL_MEMORY_START
  ldr x3, =(VIRTUAL_DEVICE_MEMORY_START - SECTION_SIZE)
  boot_create_page_block_mapping x0, x1, x2, x3, MMU_NORMAL_FLAGS, x4

  // Map device sections (virtual).
  ldr x1, =PHYSICAL_DEVICE_MEMORY_START
  ldr x2, =VIRTUAL_DEVICE_MEMORY_START
  ldr x3, =VIRTUAL_DEVICE_MEMORY_END
  boot_create_page_block_mapping x0, x1, x2, x3, MMU_DEVICE_FLAGS, x4

  // Restore link register to jump back.
  mov x30, x29
  ret
