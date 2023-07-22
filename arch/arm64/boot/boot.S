// boot.S
// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

// To keep this in the first portion of the binary.
.section ".text.boot"

// Make _start global. Need this to get execution transferred from armstub8.
.globl _start

// In 64-bit mode the boot code is loaded at 0x80000 and not 0x8000 like in 32-bit.
.org 0x80000

// Registers:
//   x0 -> 32 bit pointer to DTB in memory (primary core only) / 0 (secondary cores).
//   x1 -> 0.
//   x2 -> 0.
//   x3 -> 0.
//   x4 -> 32 bit kernel entry point, _start location.

_start:
    // Entry point for the kernel.
    // Set stack before we jump into kernel.
    ldr     x5, =_start
    mov     sp, x5

    // Also zero-out bss section to prepare kernel.
    ldr     x5, =__bss_start
    ldr     w6, =__bss_size

loop_clear_bss:
    cbz     w6, jump_kernel_entry
    str     xzr, [x5], #8
    sub     w6, w6, #1
    cbnz    w6, loop_clear_bss

jump_kernel_entry:
    // Jump to the kernel entry point.
    // This should not return.
    bl      kernel_entry

halt_forever:
    // For failsafe, halt this core.
    // We should not reach here, but if we do - we cannot recover.
    wfe
    b       halt_forever
