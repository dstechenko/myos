// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

.globl irq_local_init
.globl irq_local_enable
.globl irq_local_disable
.globl irq_local_restore
.globl irq_local_get
.globl irq_local_get_daif

irq_local_init:
  adr	x0, entry_ex_vector
  msr	vbar_el1, x0
  ret

irq_local_enable:
  msr daifclr, #2
  ret

irq_local_disable:
  mov x0, xzr
  mrs x0, daif
  msr	daifset, #2
  ret

irq_local_restore:
  msr daif, x0
  ret

irq_local_get:
  mrs x0, daif
  and x0, x0, 0x80
  ret

irq_local_get_daif:
  mrs x0, daif
  ret
