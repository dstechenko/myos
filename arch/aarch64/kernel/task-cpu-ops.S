// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/export.h>

task_cpu_switch:
  mov x2, sp
  stp x19, x20, [x0], #16
  stp x21, x22, [x0], #16
  stp x23, x24, [x0], #16
  stp x25, x26, [x0], #16
  stp x27, x28, [x0], #16
  stp x29, x2, [x0], #16
  str x30, [x0]
  ldp x19, x20, [x1], #16
  ldp x21, x22, [x1], #16
  ldp x23, x24, [x1], #16
  ldp x25, x26, [x1], #16
  ldp x27, x28, [x1], #16
  ldp x29, x2, [x1], #16
  ldr x30, [x1]
  mov sp, x2
  ret
EXPORT(task_cpu_switch);
