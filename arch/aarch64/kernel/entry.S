// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/export.h>
#include <asm/entry-defs.h>
#include <asm/registers-defs.h>

#include <uapi/syscall.h>

// To keep this in the first portion of the kernel virtual memory.
.section ".text.entry"

.macro entry_save_regs level
  sub	sp, sp, #ENTRY_STACK_FRAME_SIZE
  stp	x0, x1, [sp, #16 * 0]
  stp	x2, x3, [sp, #16 * 1]
  stp	x4, x5, [sp, #16 * 2]
  stp	x6, x7, [sp, #16 * 3]
  stp	x8, x9, [sp, #16 * 4]
  stp	x10, x11, [sp, #16 * 5]
  stp	x12, x13, [sp, #16 * 6]
  stp	x14, x15, [sp, #16 * 7]
  stp	x16, x17, [sp, #16 * 8]
  stp	x18, x19, [sp, #16 * 9]
  stp	x20, x21, [sp, #16 * 10]
  stp	x22, x23, [sp, #16 * 11]
  stp	x24, x25, [sp, #16 * 12]
  stp	x26, x27, [sp, #16 * 13]
  stp	x28, x29, [sp, #16 * 14]
  .if	\level == 0
  mrs	x21, sp_el0
  .else
  add	x21, sp, #ENTRY_STACK_FRAME_SIZE
  .endif
  mrs	x22, elr_el1
  mrs	x23, spsr_el1
  stp	x30, x21, [sp, #16 * 15]
  stp x22, x23, [sp, #16 * 16]
.endm

.macro entry_load_regs level
  ldp	x22, x23, [sp, #16 * 16]
  ldp	x30, x21, [sp, #16 * 15]
  .if	\level == 0
  msr	sp_el0, x21
  .endif
  msr	elr_el1, x22
  msr	spsr_el1, x23
  ldp	x0, x1, [sp, #16 * 0]
  ldp	x2, x3, [sp, #16 * 1]
  ldp	x4, x5, [sp, #16 * 2]
  ldp	x6, x7, [sp, #16 * 3]
  ldp	x8, x9, [sp, #16 * 4]
  ldp	x10, x11, [sp, #16 * 5]
  ldp	x12, x13, [sp, #16 * 6]
  ldp	x14, x15, [sp, #16 * 7]
  ldp	x16, x17, [sp, #16 * 8]
  ldp	x18, x19, [sp, #16 * 9]
  ldp	x20, x21, [sp, #16 * 10]
  ldp	x22, x23, [sp, #16 * 11]
  ldp	x24, x25, [sp, #16 * 12]
  ldp	x26, x27, [sp, #16 * 13]
  ldp	x28, x29, [sp, #16 * 14]
  add	sp, sp, #ENTRY_STACK_FRAME_SIZE
  eret
.endm

.macro entry_kernel_in level
  entry_save_regs \level
.endm

.macro entry_kernel_out level
  entry_load_regs \level
.endm

.macro entry_ex label
.align 7
  b \label
.endm

.macro entry_handle_invalid type, level
  entry_kernel_in level
  mov	x0, #\type
  mrs	x1, esr_el1
  mrs	x2, elr_el1
  mrs x3, far_el1
  bl entry_handle_invalid_ex
  b entry_halt_core
.endm

entry_kernel_from_boot:
  // Now should be safe to init the kernel in virtual space.
  ldr x1, =init_start
  blr x1

  // Should not reach it, but if we do - halt.
  b entry_halt_core

// TODO(dstechenko): figure this out
// balign 2048 for table
// balign  128 for entries

.align 11
entry_ex_vector:
  entry_ex entry_syn_invalid_el1t
  entry_ex entry_irq_invalid_el1t
  entry_ex entry_fiq_invalid_el1t
  entry_ex entry_err_invalid_el1t

  entry_ex entry_syn_invalid_el1h
  entry_ex entry_irq_el1
  entry_ex entry_fiq_invalid_el1h
  entry_ex entry_err_invalid_el1h

  entry_ex entry_syn_el0
  entry_ex entry_irq_el0
  entry_ex entry_fiq_invalid_el0_64
  entry_ex entry_err_invalid_el0_64

  entry_ex entry_syn_invalid_el0_32
  entry_ex entry_irq_invalid_el0_32
  entry_ex entry_fiq_invalid_el0_32
  entry_ex entry_err_invalid_el0_32
EXPORT(entry_ex_vector);

entry_irq_el1:
  entry_kernel_in 1
  bl irq_handle
  entry_kernel_out 1

entry_syn_el0:
  entry_kernel_in 0
  mrs x25, esr_el1
  lsr x24, x25, #ESR_ELx_EC_SHIFT
  cmp x24, #ESR_ELx_EC_SVC64
  beq entry_svc_el0
  cmp x24, #ESR_ELx_EC_DABT_LOW
  beq entry_da_el0
  entry_handle_invalid ENTRY_ERROR_SYN, 0

entry_irq_el0:
  entry_kernel_in 0
  bl irq_handle
  entry_kernel_out 0

entry_syn_invalid_el1t:
  entry_handle_invalid ENTRY_SYN_INVALID_EL1t, 1
entry_irq_invalid_el1t:
  entry_handle_invalid ENTRY_IRQ_INVALID_EL1t, 1
entry_fiq_invalid_el1t:
  entry_handle_invalid ENTRY_FIQ_INVALID_EL1t, 1
entry_err_invalid_el1t:
  entry_handle_invalid ENTRY_ERR_INVALID_EL1t, 1

entry_syn_invalid_el1h:
  entry_handle_invalid ENTRY_SYN_INVALID_EL1h, 1
entry_irq_invalid_el1h:
  entry_handle_invalid ENTRY_IRQ_INVALID_EL1h, 1
entry_fiq_invalid_el1h:
  entry_handle_invalid ENTRY_FIQ_INVALID_EL1h, 1
entry_err_invalid_el1h:
  entry_handle_invalid ENTRY_ERR_INVALID_EL1h, 1

entry_syn_invalid_el0_64:
  entry_handle_invalid ENTRY_SYN_INVALID_EL0_64, 0
entry_irq_invalid_el0_64:
  entry_handle_invalid ENTRY_IRQ_INVALID_EL0_64, 0
entry_fiq_invalid_el0_64:
  entry_handle_invalid ENTRY_FIQ_INVALID_EL0_64, 0
entry_err_invalid_el0_64:
  entry_handle_invalid ENTRY_ERR_INVALID_EL0_64, 0

entry_syn_invalid_el0_32:
  entry_handle_invalid ENTRY_SYN_INVALID_EL0_32, 0
entry_irq_invalid_el0_32:
  entry_handle_invalid ENTRY_IRQ_INVALID_EL0_32, 0
entry_fiq_invalid_el0_32:
  entry_handle_invalid ENTRY_FIQ_INVALID_EL0_32, 0
entry_err_invalid_el0_32:
  entry_handle_invalid ENTRY_ERR_INVALID_EL0_32, 0

entry_svc_el0:
  bl irq_local_enable
  adr x24, syscall_table
  mov x25, SYSCALL_MAX
  cmp x16, x25
  bhi entry_syscall_error
  ldr x27, [x24, x16, lsl #3]
  blr x27

entry_syscall_return:
  bl irq_local_disable
  str x0, [sp, #0]
  entry_kernel_out 0

entry_da_el0:
  bl irq_local_enable
  mrs x0, far_el1
  mrs x1, esr_el1
  bl mmu_handle_da
  cmp x0, #0
  beq entry_da_el0_out
  entry_handle_invalid ENTRY_ERROR_DATA_ABORT, 0

entry_da_el0_out:
  bl irq_local_disable
  entry_kernel_out 0

entry_syscall_error:
  entry_handle_invalid ENTRY_ERROR_SYSCALL, 0

entry_fork_return:
  bl task_schedule_tail
  cbz x19, entry_user_return
  blr x19
EXPORT(entry_fork_return);

entry_user_return:
  bl irq_local_disable
  entry_kernel_out 0

entry_halt_core:
  wfe
  b entry_halt_core
