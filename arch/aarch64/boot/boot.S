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
.globl ENTRY_POINT_LABEL

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

ENTRY_POINT_LABEL:
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
  adr x0, section_bss_start
  adr x1, section_bss_end
  sub x1, x1, x0
  bl memzero

  // Set up initial kernel/device pages.
  bl boot_create_page_tables

boot_kernel_entry:
  // Jump to the kernel entry point.
  // This should not return.
  bl kernel_start

boot_halt_core:
  // For failsafe, halt this core.
  // We should not reach here, but if we do - we cannot recover.
  wfe
  b boot_halt_core

boot_create_page_tables:
  // Save link register to return after
  mov x29, x30

  // Prepare the pages before mapping (zero out)
  adr x0, section_pgd_start
  adr x1, section_pgd_end
  sub x1, x1, x0
  bl memzero

  // Create page global directory entries
  adr x0, section_pgd_start
  mov x1, #VIRTUAL_MEMORY_START
  boot_create_page_global_directory x0, x1, x2, x3

  // Map kernel and initial stack
  mov x1, xzr
  mov x2, #VIRTUAL_MEMORY_START
  ldr x3, =(VIRTUAL_DEVICE_MEMORY_START - SECTION_SIZE)
  boot_create_page_block_mapping x0, x1, x2, x3, MMU_NORMAL_FLAGS, x4

  // Map device memory
  mov x1, #PHYSICAL_DEVICE_MEMORY_START
  ldr x2, =VIRTUAL_DEVICE_MEMORY_START
  ldr x3, =(VIRTUAL_DEVICE_MEMORY_SIZE - SECTION_SIZE)
  boot_create_page_block_mapping x0, x1, x2, x3, MMU_DEVICE_FLAGS, x4

  // Restore link register to jump back
  mov x30, x29
  ret
