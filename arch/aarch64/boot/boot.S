// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "registers.h"

// To keep this in the first portion of the binary.
.section ".text.boot"

// Make _start global. Need this to get execution transferred from armstub8.
.globl _start

  // In 64-bit mode the boot code is loaded at 0x80000 and not 0x8000 like in 32-bit.
  // Registers:
  //   x0 -> 32 bit pointer to DTB in memory (primary core only) / 0 (secondary cores).
  //   x1 -> 0.
  //   x2 -> 0.
  //   x3 -> 0.
  //   x4 -> 32 bit kernel entry point, _start location.

_start:
  // Entry point for the kernel.
  // We need to halt all of the non-primary CPUs since they
  // all might execute the same code. Depends on the firmware.
  // Check a multiprocessor affinity register to id it (0 is primary core).
  mrs     x5, mpidr_el1
  and     x5, x5, #0xFF
  cbnz    x5, boot_halt_forever

  // Check our current exception level.
  // Depending on the boot loader we could be in EL2 or EL3.
  mrs     x0, CurrentEL
  lsr     x0, x0, #2
  cmp     x0, #3
  bne     boot_init_el2

boot_init_el3:
  ldr     x0, =SCR_EL3_VALUE
  msr     scr_el3, x0
  ldr     x0, =SPSR_EL2h_VALUE
  msr     spsr_el3, x0
  adr     x0, boot_init_el2
  msr     elr_el3, x0
  eret

boot_init_el2:
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
  ldr     x5, =__bss_start
  ldr     w6, =__bss_size

boot_loop_clear_bss:
  cbz     w6, boot_jump_entry
  str     xzr, [x5], #8
  sub     w6, w6, #1
  cbnz    w6, boot_loop_clear_bss

boot_jump_entry:
  // Jump to the kernel entry point.
  // This should not return.
  bl      boot_entry

boot_halt_forever:
  // For failsafe, halt this core.
  // We should not reach here, but if we do - we cannot recover.
  wfe
  b       boot_halt_forever
