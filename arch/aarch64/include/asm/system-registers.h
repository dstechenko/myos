// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ARCH_AARCH64_ASM_SYSTEM_REGISTERS_H
#define ARCH_AARCH64_ASM_SYSTEM_REGISTERS_H

#include <kernel/util/bits.h>

/**
 * SCTLR_EL1, System Control Register (EL1).
 * See: Page 2654 of ARMv8-Architecture-Reference-Manual.
 */
#define SCTLR_EL1_RESERVED (BIT(28) | BIT(29) | BIT(22) | BIT(23) | BIT(20) | BIT(11))
#define SCTLR_EL1_EE_LITTLE_ENDIAN NOBIT(25)
#define SCTLR_EL1_EOE_LITTLE_ENDIAN NOBIT(24)
#define SCTLR_EL1_I_CACHE_DISABLED NOBIT(12)
#define SCTLR_EL1_D_CACHE_DISABLED NOBIT(2)
#define SCTLR_EL1_MMU_DISABLED NOBIT(0)
#define SCTLR_EL1_VALUE                                                                                                \
  (SCTLR_EL1_RESERVED | SCTLR_EL1_EE_LITTLE_ENDIAN | SCTLR_EL1_I_CACHE_DISABLED | SCTLR_EL1_D_CACHE_DISABLED |         \
   SCTLR_EL1_MMU_DISABLED)

/**
 * HCR_EL2, Hypervisor Configuration Register (EL2).
 * Page 2487 of ARMv8-Architecture-Reference-Manual.
 */
#define HCR_EL2_RW BIT(31)
#define HCR_EL2_VALUE HCR_EL2_RW

/**
 * SPSR_EL1h/SPSR_EL2h Saved Program Status Register (EL1/EL2).
 * Page 389 of ARMv8-Architecture-Reference-Manual.
 */
#define SPSR_MASK_ALL (BIT(6) | BIT(7) | BIT(8))
#define SPSR_EL1h (BIT(0) | BIT(2))
#define SPSR_EL2h (BIT(0) | BIT(3))
#define SPSR_EL1h_VALUE (SPSR_MASK_ALL | SPSR_EL1h)
#define SPSR_EL2h_VALUE (SPSR_MASK_ALL | SPSR_EL2h)

/**
 * SCR_EL3, Secure Configuration Register (EL3).
 * Page 2648 of ARMv8-Architecture-Reference-Manual.
 */
#define SCR_EL3_RESERVED (BIT(4) | BIT(5))
#define SCR_EL3_RW BIT(10)
#define SCR_EL3_NS BIT(0)
#define SCR_EL3_VALUE (SCR_EL3_RESERVED | SCR_EL3_RW | SCR_EL3_NS)

/**
 * ESR_EL1, Exception Syndrome Register (EL1).
 * Page 2431 of ARMv8-Architecture-Reference-Manual.
 */
#define ESR_ELx_EC_SHIFT 26
#define ESR_ELx_EC_SVC64 (BIT(4) | BIT(2) | BIT(0))
#define ESR_ELx_EC_DABT_LOW (BIT(3) | BIT(4))

#endif // !ARCH_AARCH64_SYSTEM_REGISTERS_H
