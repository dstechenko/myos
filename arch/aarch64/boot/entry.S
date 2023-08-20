// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "entry.h"
#include "boot_regs.h"

.globl entry_ex_vec, entry_fork_return

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
  stp	x22, x23, [sp, #16 * 16]
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

.macro entry_before_kernel level
  entry_save_regs level
.endm

.macro entry_after_kernel level
  entry_load_regs level
.endm

.macro entry_ex label
.align 7
  b \label
.endm

.align 11
entry_ex_vec:
  entry_ex	entry_syn_invalid_el1t
  entry_ex	entry_irq_invalid_el1t
  entry_ex	entry_fiq_invalid_el1t
  entry_ex	entry_err_invalid_el1t
  entry_ex	entry_syn_invalid_el1h
  entry_ex	entry_irq_el1
  entry_ex	entry_fiq_invalid_el1h
  entry_ex	entry_err_invalid_el1h
  entry_ex	entry_syn_el0
  entry_ex	entry_irq_el0
  entry_ex	entry_fiq_invalid_el0_64
  entry_ex	entry_err_invalid_el0_64
  entry_ex	entry_syn_invalid_el0_32
  entry_ex	entry_irq_invalid_el0_32
  entry_ex	entry_fiq_invalid_el0_32
  entry_ex	entry_err_invalid_el0_32

// Print some error message and halt.
.macro entry_handle_invalid type, level
  entry_before_kernel level
  mov	x0, #\type
  mrs	x1, esr_el1
  mrs	x2, elr_el1
  bl entry_log_invalid_message
  b entry_halt_core
.endm

// Halt the affected core.
entry_halt_core:
  wfe
  b entry_halt_core

// For now only enable el1 irqs with a proper handler.
// We need to save/load registers so that concurrent irqs can happen.
// We could unmask them before going into the handler, for simplicity make it sync.
entry_irq_el1:
  entry_before_kernel 1
  bl irq_handle
  entry_after_kernel 1

entry_syn_el0:
  entry_before_kernel 0
  mrs   x25, esr_el1
  lsr   x24, x25, #ESR_ELx_EC_SHIFT
  cmp   x24, #ESR_ELx_EC_SVC64
  b.eq  entry_svc_el0
  entry_handle_invalid ENTRY_ERROR_SYN, 0

entry_irq_el0:
  entry_before_kernel 0
  bl irq_handle
  entry_after_kernel 0

// Just abort on everything else and show the registers.
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
entry_fiq_invalid_el1h:
  entry_handle_invalid ENTRY_FIQ_INVALID_EL1h, 1
entry_err_invalid_el1h:
  entry_handle_invalid ENTRY_ERR_INVALID_EL1h, 1
entry_syn_invalid_el0_64:
  entry_handle_invalid ENTRY_SYN_INVALID_EL0_64, 0
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

syscall_num .req x25
syscall_cnt .req x26
syscall_tbl .req x27
entry_svc_el0:
  adr    syscall_tbl, syscall_table
  uxtw   syscall_num, w8
  mov    syscall_cnt, #4
  bl     irq_enable
  cmp    syscall_num, syscall_cnt
  b.hs   entry_syscall_error
  ldr    x16, [syscall_tbl, syscall_num, lsl #3]
  blr    x16
  b      entry_syscall_return

entry_syscall_error:
  entry_handle_invalid ENTRY_ERROR_SYSCALL, 0

entry_syscall_return:
  bl    irq_disable
  str   x0, [sp, #0]
  entry_after_kernel 0

fork_addr .req x19
entry_fork_return:
  bl  task_schedule_tail
  blr fork_addr

entry_user_return:
