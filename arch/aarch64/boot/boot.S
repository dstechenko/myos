// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/page.h>
#include <asm/system-registers.h>

// To keep this in the first portion of the binary.
.section ".text.boot"

// Make _start global. Need this to get execution transferred from armstub8.
.globl _start, boot_start

.macro boot_create_table_entry table, vaddr, shift, tmp1, tmp2
  lsr   \tmp1, \virt, #\shift
  and   \tmp1, \tmp1, #PTRS_PER_TABLE - 1
  add   \tmp2, \table, #PAGE_SIZE
  orr   \tmp2, \tmp2, #MM_TYPE_PAGE_TABLE
.endm

.macro boot_create_block_map
.endm

_start:
boot_start:
  // Entry point for the kernel.
  // We need to halt all of the non-primary CPUs since they
  // all might execute the same code. Depends on the firmware.
  // Check a multiprocessor affinity register to id it (0 is primary core).
  mrs     x5, mpidr_el1
  and     x5, x5, #0xFF
  cbnz    x5, boot_halt_core

  // Check our current exception level.
  // Depending on the boot loader we could be in EL2 or EL3.
  mrs     x0, CurrentEL
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
  ldr     x5, =_start
  mov     sp, x5

  // Also zero-out bss section to prepare kernel.
  adr     x0, __bss_start
  adr     x1, __bss_size
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
