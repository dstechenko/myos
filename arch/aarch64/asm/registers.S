// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/export.h>

registers_get_pstate_nzcv:
  mrs x0, NZCV
  ret
EXPORT(registers_get_pstate_nzcv);

registers_set_pstate_nzcv:
  msr NZCV, x0
  ret
EXPORT(registers_set_pstate_nzcv);

registers_get_pstate_daif:
  mrs x0, DAIF
  ret
EXPORT(registers_get_pstate_daif);

registers_set_pstate_daif:
  msr DAIF, x0
  ret
EXPORT(registers_set_pstate_daif);

registers_get_pstate_el:
  mrs x0, CurrentEL
  ret
EXPORT(registers_get_pstate_el);

registers_get_pstate_spsel:
  mrs x0, SPSel
  ret
EXPORT(registers_get_pstate_spsel);

registers_set_pstate_spsel:
  msr SPSel, x0
  ret
EXPORT(registers_set_pstate_spsel);

registers_get_pstate_pan:
  mrs x0, SPSel
  ret
EXPORT(registers_get_pstate_pan);

registers_set_pstate_pan:
  msr SPSel, x0
  ret
EXPORT(registers_set_pstate_pan);

registers_get_pstate_uao:
  mrs x0, SPSel
  ret
EXPORT(registers_get_pstate_uao);

registers_set_pstate_uao:
  msr SPSel, x0
  ret
EXPORT(registers_set_pstate_uao);

registers_get_spsr_el1:
  mrs x0, SPSR_EL1
  ret
EXPORT(registers_get_spsr_el1);

registers_set_spsr_el1:
  msr SPSR_EL1, x0
  ret
EXPORT(registers_set_spsr_el1);

registers_get_esr_el1:
  mrs x0, ESR_EL1
  ret
EXPORT(registers_get_esr_el1);

registers_set_esr_el1:
  msr ESR_EL1, x0
  ret
EXPORT(registers_set_esr_el1);

registers_get_elr_el1:
  mrs x0, ELR_EL1
  ret
EXPORT(registers_get_elr_el1);

registers_set_elr_el1:
  msr ELR_EL1, x0
  ret
EXPORT(registers_set_elr_el1);

registers_get_far_el1:
  mrs x0, FAR_EL1
  ret
EXPORT(registers_get_far_el1);

registers_set_far_el1:
  msr FAR_EL1, x0
  ret
EXPORT(registers_set_far_el1);
