// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/export.h>

registers_get_pstate_nzcv:
  mrs x0, nzcv
  ret
EXPORT(registers_get_pstate_nzcv);

registers_set_pstate_nzcv:
  msr nzcv, x0
  ret
EXPORT(registers_set_pstate_nzcv);

registers_get_pstate_daif:
  mrs x0, daif
  ret
EXPORT(registers_get_pstate_daif);

registers_set_pstate_daif:
  msr daif, x0
  ret
EXPORT(registers_set_pstate_daif);

registers_get_pstate_el:
  mrs x0, currentel
  ret
EXPORT(registers_get_pstate_el);

registers_get_pstate_spsel:
  mrs x0, spsel
  ret
EXPORT(registers_get_pstate_spsel);

registers_set_pstate_spsel:
  msr spsel, x0
  ret
EXPORT(registers_set_pstate_spsel);

registers_get_spsr_el1:
  mrs x0, spsr_el1
  ret
EXPORT(registers_get_spsr_el1);

registers_set_spsr_el1:
  msr spsr_el1, x0
  ret
EXPORT(registers_set_spsr_el1);

registers_get_esr_el1:
  mrs x0, esr_el1
  ret
EXPORT(registers_get_esr_el1);

registers_set_esr_el1:
  msr esr_el1, x0
  ret
EXPORT(registers_set_esr_el1);

registers_get_elr_el1:
  mrs x0, elr_el1
  ret
EXPORT(registers_get_elr_el1);

registers_set_elr_el1:
  msr elr_el1, x0
  ret
EXPORT(registers_set_elr_el1);

registers_get_far_el1:
  mrs x0, far_el1
  ret
EXPORT(registers_get_far_el1);

registers_set_far_el1:
  msr far_el1, x0
  ret
EXPORT(registers_set_far_el1);

registers_get_mpidr_el1:
  mrs x0, mpidr_el1
  ret
EXPORT(registers_get_mpidr_el1);

registers_get_ttbr0_el1:
  mrs x0, ttbr0_el1
  ret
EXPORT(registers_get_ttbr0_el1);

registers_set_ttbr0_el1:
  msr ttbr0_el1, x0
  ret
EXPORT(registers_set_ttbr0_el1);

registers_get_ttbr1_el1:
  mrs x0, ttbr1_el1
  ret
EXPORT(registers_get_ttbr1_el1);

registers_set_ttbr1_el1:
  msr ttbr1_el1, x0
  ret
EXPORT(registers_set_ttbr1_el1);

registers_get_vbar_el1:
  mrs x0, vbar_el1
  ret
EXPORT(registers_get_vbar_el1);

registers_set_vbar_el1:
  msr vbar_el1, x0
  ret
EXPORT(registers_set_vbar_el1);
