// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef DRIVERS_BOARD_BCM2711_IRQ_H
#define DRIVERS_BOARD_BCM2711_IRQ_H

#include <kernel/bits.h>

/**
 * The base address for the ARM interrupt register is 0x7E00B000.
 *
 * The ARM has two types of interrupt sources:
 *   1. Interrupts coming from the GPU peripherals.
 *   2. Interrupts coming from local ARM control peripherals.
 *
 * The ARM processor gets three types of interrupts:
 *   1. Interrupts from ARM specific peripherals.
 *   2. Interrupts from GPU peripherals.
 *   3. Special events interrupts.
 *
 * The ARM specific interrupts are:
 *   - One timer.
 *   - One mailbox.
 *   - Two doorbells.
 *   - Two GPU halted interrupts.
 *   - Two address/access error interrupt.
 *
 * The mailbox and doorbell registers are not for general usage.
 * For each interrupt source (ARM or GPU) there is an interrupt enable bit
 * (read/write) and an interrupt pending bit (Read Only). All interrupts
 * generated by the arm control block are level sensitive interrupts. Thus all
 * interrupts remain asserted until disabled or the interrupt source is cleared.
 * Default the interrupts from doorbell 0,1 and mailbox 0 go to the ARM this
 * means that these resources should be written by the GPU and read by the ARM.
 * The opposite holds for doorbells 2, 3 and mailbox 1.
 */

#define IRQ_BASE 0x0000B000

#define IRQ_BASIC_PENDING (IRQ_BASE + 0x200)
#define IRQ_PENDING_1 (IRQ_BASE + 0x204)
#define IRQ_PENDING_2 (IRQ_BASE + 0x208)
#define IRQ_FIQ_CTRL (IRQ_BASE + 0x20C)
#define IRQ_ENABLE_1 (IRQ_BASE + 0x210)
#define IRQ_ENABLE_2 (IRQ_BASE + 0x214)
#define IRQ_ENABLE_BASIC (IRQ_BASE + 0x218)
#define IRQ_DISABLE_1 (IRQ_BASE + 0x21C)
#define IRQ_DISABLE_2 (IRQ_BASE + 0x220)
#define IRQ_DISABLE_BASIC (IRQ_BASE + 0x224)

#define IRQ_TABLE_SYSTEM_TIMER_0 BIT(0)
#define IRQ_TABLE_SYSTEM_TIMER_1 BIT(1)
#define IRQ_TABLE_SYSTEM_TIMER_2 BIT(2)
#define IRQ_TABLE_SYSTEM_TIMER_3 BIT(3)

void irq_ctrl_init(void);

#endif  // !DRIVERS_BOARD_BCM2711_IRQ_H
