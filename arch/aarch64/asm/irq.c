// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/irq.h>
#include <asm/registers.h>
#include <asm/sections.h>

#include <kernel/ptrs.h>

SECTIONS_LABEL(entry_ex_vector);

void irq_local_init(void) {
  const uintptr_t vbar = REF_TO_ADR(entry_ex_vector);
  registers_set_vbar_el1(vbar);
}

void irq_local_enable(void) {
  const irqflags_t daif = registers_get_pstate_daif();
  irq_local_restore(REGISTERS_PSTATE_ENABLE_I(daif));
}

irqflags_t irq_local_disable(void) {
  const irqflags_t daif = registers_get_pstate_daif();
  irq_local_restore(REGISTERS_PSTATE_DISABLE_I(daif));
  return daif;
}

void irq_local_restore(irqflags_t flags) { registers_set_pstate_daif(flags); }

bool irq_local_disabled(void) {
  const irqflags_t daif = registers_get_pstate_daif();
  return REGISTERS_PSTATE_SELECT_I(daif);
}
