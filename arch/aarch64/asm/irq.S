// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

.globl irq_init, irq_enable, irq_disable

vector_ptr .req x0
irq_init:
  adr	vector_ptr, entry_ex_vec
  msr	vbar_el1, vector_ptr
  ret

irq_enable:
  msr daifclr, #2
  ret

irq_disable:
  msr	daifset, #2
  ret
