// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <uapi/syscall.h>

.globl syscall_alloc
.globl syscall_clone
.globl syscall_exit
.globl syscall_write
.globl syscall_delay

syscall_alloc:
  mov w8, #SYSCALL_ALLOC_NUM
  svc #0
  ret

syscall_clone:
  mov w8, #SYSCALL_CLONE_NUM
  svc #0
  ret

syscall_exit:
  mov w8, #SYSCALL_EXIT_NUM
  svc #0
  ret

syscall_write:
  mov w8, #SYSCALL_WRITE_NUM
  svc #0
  ret

syscall_delay:
  mov w8, #SYSCALL_DELAY_NUM
  svc #0
  ret
