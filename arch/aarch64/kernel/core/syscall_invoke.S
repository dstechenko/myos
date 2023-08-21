// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "syscall_invoke.h"

.globl syscall_alloc_invoke
.globl syscall_clone_invoke
.globl syscall_exit_invoke
.globl syscall_write_invoke

syscall_num .req w8
syscall_alloc_invoke:
  mov syscall_num, #SYSCALL_ALLOC_NUM
  svc #0
  ret

clone_pc .req x10
clone_sp .req x11
syscall_clone_invoke:
  mov clone_pc, x0
  mov clone_sp, x1
  mov x0, clone_sp
  mov syscall_num, #SYSCALL_CLONE_NUM
  svc #0
  cmp x0, #0
  beq syscall_clone_thread_start
  ret

clone_fp .req x29
syscall_clone_thread_start:
  mov clone_fp, #0
  blr clone_pc
  bl  syscall_exit_invoke

syscall_exit_invoke:
  mov syscall_num, #SYSCALL_EXIT_NUM
  svc #0
  ret

syscall_write_invoke:
  mov syscall_num, #SYSCALL_WRITE_NUM
  svc #0
  ret
