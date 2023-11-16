// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

.globl local_irq_init, local_irq_enable, local_irq_disable

local_irq_init:
  adr	x0, entry_ex_vector
  msr	vbar_el1, x0
  ret

local_irq_enable:
  msr daifclr, #2
  ret

local_irq_disable:
  msr	daifset, #2
  ret
