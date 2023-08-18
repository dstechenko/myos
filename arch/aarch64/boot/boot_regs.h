// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ARCH_AARCH64_BOOT_BOOT_REGS_H
#define ARCH_AARCH64_BOOT_BOOT_REGS_H

#define SET(b) (1 << b)
#define UNSET(b) (0 << b)

/**
 * SCTLR_EL1, System Control Register (EL1).
 * See: Page 2654 of ARMv8-Architecture-Reference-Manual.
 */
#define SCTLR_EL1_RESERVED                                                     \
  (SET(28) | SET(29) | SET(22) | SET(23) | SET(20) | SET(11))
#define SCTLR_EL1_EE_LITTLE_ENDIAN UNSET(25)
#define SCTLR_EL1_EOE_LITTLE_ENDIAN UNSET(24)
#define SCTLR_EL1_I_CACHE_DISABLED UNSET(12)
#define SCTLR_EL1_D_CACHE_DISABLED UNSET(2)
#define SCTLR_EL1_MMU_DISABLED UNSET(0)
#define SCTLR_EL1_VALUE                                                        \
  (SCTLR_EL1_RESERVED | SCTLR_EL1_EE_LITTLE_ENDIAN |                           \
   SCTLR_EL1_I_CACHE_DISABLED | SCTLR_EL1_D_CACHE_DISABLED |                   \
   SCTLR_EL1_MMU_DISABLED)

/**
 * HCR_EL2, Hypervisor Configuration Register (EL2).
 * Page 2487 of ARMv8-Architecture-Reference-Manual.
 */
#define HCR_EL2_RW SET(31)
#define HCR_EL2_VALUE HCR_EL2_RW

/**
 * SPSR_EL1h/SPSR_EL2h Saved Program Status Register (EL1/EL2).
 * Page 389 of ARMv8-Architecture-Reference-Manual.
 */
#define SPSR_MASK_ALL (SET(6) | SET(7) | SET(8))
#define SPSR_EL1h (SET(0) | SET(2))
#define SPSR_EL2h (SET(0) | SET(3))
#define SPSR_EL1h_VALUE (SPSR_MASK_ALL | SPSR_EL1h)
#define SPSR_EL2h_VALUE (SPSR_MASK_ALL | SPSR_EL2h)

/**
 * SCR_EL3, Secure Configuration Register (EL3).
 * Page 2648 of ARMv8-Architecture-Reference-Manual.
 */
#define SCR_EL3_RESERVED (SET(4) | SET(5))
#define SCR_EL3_RW SET(10)
#define SCR_EL3_NS SET(0)
#define SCR_EL3_VALUE (SCR_EL3_RESERVED | SCR_EL3_RW | SCR_EL3_NS)

#endif // !ARCH_AARCH64_BOOT_BOOT_REGS_H
