// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "syscall-invoke.h"

.globl syscall_alloc_invoke
.globl syscall_clone_invoke
.globl syscall_exit_invoke
.globl syscall_write_invoke
.globl syscall_cdelay_invoke

syscall_alloc_invoke:
  mov w8, #SYSCALL_ALLOC_NUM
  svc #0
  ret

syscall_clone_invoke:
  mov w8, #SYSCALL_CLONE_NUM
  svc #0
  ret

syscall_exit_invoke:
  mov w8, #SYSCALL_EXIT_NUM
  svc #0
  ret

syscall_write_invoke:
  mov w8, #SYSCALL_WRITE_NUM
  svc #0
  ret

syscall_cdelay_invoke:
  mov w8, #SYSCALL_CDELAY_NUM
  svc #0
  ret
