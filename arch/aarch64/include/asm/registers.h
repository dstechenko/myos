// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ARCH_AARCH64_ASM_REGISTERS_H
#define ARCH_AARCH64_ASM_REGISTERS_H

#include <kernel/bits.h>
#include <kernel/types.h>

/**
 * The AArch64 ISA.
 *   AArch64 defines 31 general purpose registers which can be used to store 64 or
 *   32-bit values and you may find them referenced either as Xn, Wn or Rn.
 * R0_R30:
 *   Here n is from 0 to 30, Xn for 64-bit, Wn for 32-bit, Rn is more general irrelevant to the size.
 *
 * The AArch64 ABI.
 * R0_R7:
 *   Are used to save arguments when calling a function, while the R0 is used also to store
 *   the result which is returned by a function.
 * R8:
 *   Indirect result location register, used in C++ for returning non-trivial objects (set by the caller).
 * R9_R15:
 *   Known as scratch registers, can be used any time without any assumptions about their contents.
 * R16_R17:
 *   Intra-procedure-call temporary registers, the linker may use these in PLT code.
 *   Can be used as temporary registers between calls.
 * R18:
 *   Platform register, reserved for the use of platform ABI. For example, for the windows ABI,
 *   in kernel mode, points to KPCR for the current processor; in user mode, points to TEB.
 * R19_R28:
 *   Can also be used as scratch registers, but their contents must be saved before usage
 *   and restored afterwards.
 * R29:
 *   Used as a Frame Pointer, pointing to the current stack frame and it is usually
 *   useful when the program runs under a debugger. The GNU C compiler has an option to use R29 as a
 *   general purpose register via the -fomit-frame-pointer option.
 * R30:
 *   Known as the link register (LR) and it can be used to store the return address during
 *   a function call, an alternative of saving the address to the call stack. Certain branch and link
 *   instructions store the current address to the link register before the program counter
 *   (the register that holds the address of the next instruction) loads the new address.
 * SP:
 *   Stores the address corresponding to the end of the stack (or as commonly said pointing to the
 *   top of the stack). This address will change when registers are pushed into the stack or
 *   during the allocation or deletion of local variables.
 * PC:
 *   Holds the next address which contains the code to be executed. It is increased automatically
 *   by four after each instruction while it can be modified by a small number of instructions
 *   (e.g. adr or ldr). This gives the ability of jumping to a new address and start executing code from
 * there. ZR: Referenced as ZR, XZR or WZR, is a special register that is hard-wired to the integer value 0.
 *   Writing to that register is always discarded and reading its value will always result in a 0 being read.
 * PSTATE:
 * SPSR_ELx:
 *   The current state of the processor is stored within separate PSTATE fields.
 *   If an exception is taken, the PSTATE information is saved in the Saved Program Status Register (SPSR_ELn)
 *   which exists as SPSR_EL3, SPSR_EL2, and SPSR_EL1. All the parts accessed via special registers:
 *   DAIF, NZCV, CurrentEL, SPSel, PAN, UAO.
 * ESR_ELx:
 *   Exception syndrom register, saves syndrom information about the exception type taken to level X.
 * ELR_ELx:
 *   Exception link register, saves the preferred return address when taking an exception to level X.
 * FAR_ELx:
 *   Fault address register, saves the faulting virtual address for all synchronous instruction or data
 *   aborts, PC alignment faults and Watchpoint exceptions that are taken to level X.
 * MPIDR_ELx:
 *   Multiprocessor affinity register, in a multiprocessor system, provides an additional
 *   PE identification mechanism for scheduling purposes.
 * TTBR0_EL1:
 *   Translation table base register 0, holds the base address of the translation table for the
 *   initial lookup for stage 1 of the translation of an address from the lower VA range in the
 *   level 1&0 translation regime, and other information for this translation regime.
 * TTBR0_EL1:
 *   Translation table base register 1, holds the base address of the translation table for the
 *   initial lookup for stage 1 of the translation of an address from the lower VA range in the
 *   level 1&0 translation regime, and other information for this translation regime.
 * VBAR_EL1:
 *   Vector base address register, holds the vector base address for any exception that is taken to level 1.
 */

#define REGISTERS_PSTATE_SELECT_N(state) SELECT_BIT(state, 31)
#define REGISTERS_PSTATE_SELECT_Z(state) SELECT_BIT(state, 30)
#define REGISTERS_PSTATE_SELECT_C(state) SELECT_BIT(state, 29)
#define REGISTERS_PSTATE_SELECT_V(state) SELECT_BIT(state, 28)
uint32_t registers_get_pstate_nzcv(void);
void registers_set_pstate_nzcv(uint32_t nzcv);

#define REGISTERS_PSTATE_SELECT_D(state) SELECT_BIT(state, 9)
#define REGISTERS_PSTATE_SELECT_A(state) SELECT_BIT(state, 8)
#define REGISTERS_PSTATE_SELECT_I(state) SELECT_BIT(state, 7)
#define REGISTERS_PSTATE_SELECT_F(state) SELECT_BIT(state, 6)
#define REGISTERS_PSTATE_ENABLE_D(state) ENABLE_BIT(state, 9)
#define REGISTERS_PSTATE_ENABLE_A(state) ENABLE_BIT(state, 8)
#define REGISTERS_PSTATE_ENABLE_I(state) ENABLE_BIT(state, 7)
#define REGISTERS_PSTATE_ENABLE_F(state) ENABLE_BIT(state, 6)
#define REGISTERS_PSTATE_DISABLE_D(state) DISABLE_BIT(state, 9)
#define REGISTERS_PSTATE_DISABLE_A(state) DISABLE_BIT(state, 8)
#define REGISTERS_PSTATE_DISABLE_I(state) DISABLE_BIT(state, 7)
#define REGISTERS_PSTATE_DISABLE_F(state) DISABLE_BIT(state, 6)
uint32_t registers_get_pstate_daif(void);
void registers_set_pstate_daif(uint32_t daif);

#define REGISTERS_PSTATE_SELECT_EL(state) SELECT_BITS(state, 2, BIT(3) | BIT(2))
uint32_t registers_get_pstate_el(void);

#define REGISTERS_PSTATE_SELECT_SPSEL(state) SELECT_BIT(state, 0)
uint32_t registers_get_pstate_spsel(void);
void registers_set_pstate_spsel(uint32_t spsel);

#define REGISTERS_PSTATE_SELECT_PAN(state) SELECT_BIT(state, 22)
#define REGISTERS_PSTATE_SELECT_UAO(state) SELECT_BIT(state, 23)
uint32_t registers_get_spsr_el1(void);
void registers_set_spsr_el1(uint32_t spsr);

uint32_t registers_get_esr_el1(void);
void registers_set_esr_el1(uint32_t esr);

uint64_t registers_get_elr_el1(void);
void registers_set_elr_el1(uint64_t elr);

uint64_t registers_get_far_el1(void);
void registers_set_far_el1(uint64_t far);

#define REGISTERS_MPIDR_SELECT_AFF0(mpidr) MASK_LOW_BYTE(mpidr)
uint64_t registers_get_mpidr_el1(void);

uint64_t registers_get_ttbr0_el1(void);
void registers_set_ttbr0_el1(uint64_t ttbr);

uint64_t registers_get_ttbr1_el1(void);
void registers_set_ttbr1_el1(uint64_t ttbr);

uint64_t registers_get_vbar_el1(void);
void registers_set_vbar_el1(uint64_t vbar);

#endif  // !ARCH_AARCH64_ASM_REGISTERS_H
