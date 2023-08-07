// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_AARCH64_BOOT_REGISTERS_H
#define ASM_AARCH64_BOOT_REGISTERS_H

/**
 * SCTLR_EL1, System Control Register (EL1).
 * See: Page 2654 of ARMv8-Architecture-Reference-Manual.
 */
#define SCTLR_EL1_RESERVED ((3 << 28) | (3 << 22) | (1 << 20) | (1 << 11))
#define SCTLR_EL1_EE_LITTLE_ENDIAN (0 << 25)
#define SCTLR_EL1_EOE_LITTLE_ENDIAN (0 << 24)
#define SCTLR_EL1_I_CACHE_DISABLED (0 << 12)
#define SCTLR_EL1_D_CACHE_DISABLED (0 << 2)
#define SCTLR_EL1_MMU_DISABLED (0 << 0)
#define SCTLR_EL1_VALUE                                                        \
  (SCTLR_EL1_RESERVED | SCTLR_EL1_EE_LITTLE_ENDIAN |                           \
   SCTLR_EL1_I_CACHE_DISABLED | SCTLR_EL1_D_CACHE_DISABLED |                   \
   SCTLR_EL1_MMU_DISABLED)

/**
 * HCR_EL2, Hypervisor Configuration Register (EL2).
 * Page 2487 of ARMv8-Architecture-Reference-Manual.
 */
#define HCR_EL2_RW (1 << 31)
#define HCR_EL2_VALUE HCR_EL2_RW

/**
 * SPSR_EL1h/SPSR_EL2h Saved Program Status Register (EL1/EL2).
 * Page 389 of ARMv8-Architecture-Reference-Manual.
 */
#define SPSR_MASK_ALL (7 << 6)
#define SPSR_EL1h (5 << 0)
#define SPSR_EL2h (9 << 0)
#define SPSR_EL1h_VALUE (SPSR_MASK_ALL | SPSR_EL1h)
#define SPSR_EL2h_VALUE (SPSR_MASK_ALL | SPSR_EL2h)

/**
 * SCR_EL3, Secure Configuration Register (EL3).
 * Page 2648 of ARMv8-Architecture-Reference-Manual.
 */
#define SCR_EL3_RESERVED (3 << 4)
#define SCR_EL3_RW (1 << 10)
#define SCR_EL3_NS (1 << 0)
#define SCR_EL3_VALUE (SCR_EL3_RESERVED | SCR_EL3_RW | SCR_EL3_NS)

#endif // !ASM_AARCH64_BOOT_REGISTERS_H
