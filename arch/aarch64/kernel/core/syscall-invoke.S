// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "syscall-invoke.h"

.globl syscall_alloc_invoke
.globl syscall_clone_invoke
.globl syscall_exit_invoke
.globl syscall_write_invoke

syscall_alloc_invoke:
  mov w8, #SYSCALL_ALLOC_NUM
  svc #0
  ret

syscall_clone_invoke:
  mov x10, x0
  mov x11, x1
  mov x0, x1
  mov w8, #SYSCALL_CLONE_NUM
  svc #0
  cmp x0, #0
  beq syscall_clone_thread_start
  ret

syscall_clone_thread_start:
  mov x29, xzr
  blr x10
  bl  syscall_exit_invoke

syscall_exit_invoke:
  mov w8, #SYSCALL_EXIT_NUM
  svc #0
  ret

syscall_write_invoke:
  mov w8, #SYSCALL_WRITE_NUM
  svc #0
  ret
