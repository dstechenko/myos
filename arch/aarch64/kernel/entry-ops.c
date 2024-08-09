// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/cpu.h>
#include <asm/registers.h>

#include <kernel/assert.h>
#include <kernel/print.h>
#include <kernel/types.h>

static const char *const entry_invalid_types[] = {
    "SYN_INVALID_EL1t",   "IRQ_INVALID_EL1t",   "FIQ_INVALID_EL1t",   "ERR_INVALID_EL1t",
    "SYN_INVALID_EL1h",   "IRQ_INVALID_EL1h",   "FIQ_INVALID_EL1h",   "ERR_INVALID_EL1h",
    "SYN_INVALID_EL0_64", "IRQ_INVALID_EL0_64", "FIQ_INVALID_EL0_64", "ERR_INVALID_EL0_64",
    "SYN_INVALID_EL0_32", "IRQ_INVALID_EL0_32", "FIQ_INVALID_EL0_32", "ERR_INVALID_EL0_32",
    "ERROR_SYN",          "ERROR_SYSCALL",      "ERROR_DATA_ABORT",
};

void entry_handle_invalid_ex(const uint8_t type) {
  const uint32_t spsr = registers_get_spsr_el1();
  ASSERT(type < sizeof(entry_invalid_types) / sizeof(*entry_invalid_types));
  print(
      "\n"
      "Core crashed!\n"
      "  Type=%s\n"
      "  Core=%d\n"
      "  Level=%d\n"
      "  ESR=%x\n"
      "  ELR=%lx\n"
      "  FAR=%lx\n"
      "  SPSR=%x\n"
      "  [N=%d,Z=%d,C=%d,V=%d,D=%d,A=%d,I=%d,F=%d,SPSel=%d,PAN=%d,UAO=%d]\n"
      "\n",
      /* Type = */ entry_invalid_types[type],
      /* Core = */ cpu_get_core(),
      /* Level = */ REGISTERS_PSTATE_EL(registers_get_pstate_el()),
      /* ESR = */ registers_get_esr_el1(),
      /* ELR = */ registers_get_elr_el1(),
      /* FAR = */ registers_get_far_el1(),
      /* SPSR = */ spsr,
      /* N = */ REGISTERS_PSTATE_N(spsr),
      /* Z = */ REGISTERS_PSTATE_Z(spsr),
      /* C = */ REGISTERS_PSTATE_C(spsr),
      /* V = */ REGISTERS_PSTATE_V(spsr),
      /* D = */ REGISTERS_PSTATE_D(spsr),
      /* A = */ REGISTERS_PSTATE_A(spsr),
      /* I = */ REGISTERS_PSTATE_I(spsr),
      /* F = */ REGISTERS_PSTATE_F(spsr),
      /* SPSel = */ REGISTERS_PSTATE_SPSEL(spsr),
      /* PAN = */ REGISTERS_PSTATE_PAN(spsr),
      /* UAO = */ REGISTERS_PSTATE_UAO(spsr));
}
