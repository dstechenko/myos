// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "irq.h"

#include <drivers/irq.h>
#include <drivers/mmio.h>

#include "timer.h"

// TODO(dstechenko): clean this up
#include <kernel/log.h>

/* #define MMIO_BASE 0 */

/* void mmio_write32(const uint64_t reg, const uint32_t data) { */
/*   *(volatile uint32_t *)((uintptr_t)MMIO_BASE + reg) = data; */
/* } */

/* uint32_t mmio_read32(const uint64_t reg) { */
/*   return *(volatile uint32_t *)((uintptr_t)MMIO_BASE + reg); */
/* } */

/* static void enable_interrupt(unsigned int irq) { */
/*    // printf("%x\r\n", irq); */
/*    unsigned int n = irq / 32; */
/*    unsigned int offset = irq % 32; */
/*    unsigned int enableRegister = GICD_ENABLE_IRQ_BASE + (4*n); */
/*    // printf("EnableRegister: %x\r\n", enableRegister); */
/*    mmio_write32(enableRegister, 1 << offset); */
/* } */

/* static void assign_target(unsigned int irq, unsigned int cpu) { */
/*    unsigned int n = irq / 4; */
/*    unsigned int targetRegister = GIC_IRQ_TARGET_BASE + (4*n); */
/*    // Currently we only enter the target CPU 0 */
/*    mmio_write32(targetRegister, mmio_read32(targetRegister) | (1 << 8)); */
/* } */

/* static void enable_interrupt_controller() { */
/*    assign_target(SYSTEM_TIMER_IRQ_1, 0); */
/*    enable_interrupt(SYSTEM_TIMER_IRQ_1); */
/* } */

void irq_ctrl_init(void) {
  /* enable_interrupt_controller(); */
  mmio_write32(IRQ_ENABLE_0, IRQ_TABLE_SYSTEM_TIMER_1);
}

void irq_handle(void) {
  uint32_t irq = mmio_read32(IRQ_PENDING_0);

  while (irq) {
    if (irq & IRQ_TABLE_SYSTEM_TIMER_1) {
      irq &= ~IRQ_TABLE_SYSTEM_TIMER_1;
      timer_handle();
    }
  }

  /*  unsigned int irq_ack_reg = mmio_read32(GICC_IAR); */
  /*  unsigned int irq = irq_ack_reg & 0x2FF; */
  /*  switch (irq) { */
  /*    case (SYSTEM_TIMER_IRQ_1): */
  /*      timer_handle(); */
  /*      mmio_write32(GICC_EOIR, irq_ack_reg); */
  /*      break; */
  /*    default: */
  /*      // printf("Unknown pending irq: %x\r\n", irq); */
  /*      break; */
  /* } */
}
