// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

.globl local_irq_init
.globl local_irq_enable
.globl local_irq_disable
.globl local_irq_restore
.globl local_irq_enabled

local_irq_init:
  adr	x0, entry_ex_vector
  msr	vbar_el1, x0
  ret

local_irq_enable:
  msr daifclr, #2
  ret

local_irq_disable:
  mrs x0, daif
  msr	daifset, #2
  ret

local_irq_restore:
  msr daif, x0
  ret

local_irq_enabled:
  mrs x0, daif
  and x0, x0, #2
  ret
