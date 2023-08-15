// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

.globl irq_init
irq_init:
  adr	x0, entry_ex_vec
  msr	vbar_el1, x0
  ret

.globl irq_enable
irq_enable:
  msr daifclr, #2
  ret

.globl irq_disable
irq_disable:
  msr	daifset, #2
  ret
