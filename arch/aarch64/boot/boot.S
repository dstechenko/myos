// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/page.h>
#include <asm/system-registers.h>

// To keep this in the first portion of the binary.
.section ".text.boot"

// Make _start global. Need this to get execution transferred from armstub8.
.globl _start, boot_start

.macro boot_create_page_global_directory_entry table, vaddr, aux0, aux1
  boot_create_page_table_entry \table, \vaddr, PAGE_GLOBAL_DIRECTORY_SHIFT, \aux0, \aux1
  boot_create_page_table_entry \table, \vaddr, PAGE_UPPER_DIRECTORY_SHIFT, \aux0, \aux1
.endm

.macro boot_create_page_table_entry table, vaddr, shift, aux0, aux1
  ## lsr   \aux0, \virt, #\shift
  ## and   \aux0, \aux0, #PAGE_ENTRIES_PER_TABLE - 1
  ## add   \aux1, \table, #PAGE_SIZE
  ## orr   \aux1, \aux1, #MM_TYPE_PAGE_TABLE
.endm

.macro boot_create_page_block_mapping table, paddr, start, end, flags, aux0
.endm

_start:
boot_start:
  // Entry point for the kernel.
  // We need to halt all of the non-primary CPUs since they
  // all might execute the same code. Depends on the firmware.
  // Check a multiprocessor affinity register to id it (0 is primary core).
  mrs     x0, mpidr_el1
  and     x0, x0, #0xFF
  cbnz    x0, boot_halt_core

  // Check our current exception level.
  // Depending on the boot loader we could be in EL2 or EL3.
  mrs     x0, currentel
  lsr     x0, x0, #2
  cmp     x0, #3
  bne     boot_init_el2

boot_init_el3:
  // Set EL3 secure configurations and switch to EL2.
  ldr     x0, =SCR_EL3_VALUE
  msr     scr_el3, x0
  ldr     x0, =SPSR_EL2h_VALUE
  msr     spsr_el3, x0
  adr     x0, boot_init_el2
  msr     elr_el3, x0
  eret

boot_init_el2:
  // Set hypervisor and system control configurations and
  // switch to EL1 for kernel entry.
  // Disabling MMU, IRQs and data/instruction caching.
  ldr     x0, =SCTLR_EL1_VALUE
  msr     sctlr_el1, x0
  ldr     x0, =HCR_EL2_VALUE
  msr     hcr_el2, x0
  ldr     x0, =SPSR_EL1h_VALUE
  msr     spsr_el2, x0
  adr     x0, boot_init_kernel
  msr     elr_el2, x0
  eret

boot_init_kernel:
  // Set stack before we jump into kernel.
  ldr     x0, =_start
  mov     sp, x0

  // Also zero-out bss section to prepare kernel.
  adr     x0, section_bss_start
  adr     x1, section_bss_end
  sub     x1, x1, x0
  bl      memzero

boot_kernel_entry:
  // Jump to the kernel entry point.
  // This should not return.
  bl      kernel_start

boot_halt_core:
  // For failsafe, halt this core.
  // We should not reach here, but if we do - we cannot recover.
  wfe
  b       boot_halt_core

boot_create_page_tables:
  // Save link register to return after
  mov	x29, x30

  // Prepare the pages before mapping (zero out)
  ## adrp	x0, page_global_directory
  ## mov	x1, #PG_DIR_SIZE
  ## bl  memzero

  // Create page global directory entries
  ## adrp	x0, page_global_directory
  ## mov	x1, #VA_START
  ## boot_create_page_global_directory_entry x0, x1, x2, x3

  // Map kernel and initial stack
  // ...

  // Map device memory
  // ...

  // Restore link register to jump back
  mov x30, x29

  ret
