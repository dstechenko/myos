// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef UAPI_SYSCALL_H
#define UAPI_SYSCALL_H

#ifndef __ASSEMBLER__
#include <stddef.h>
#include <stdint.h>

uintptr_t syscall_alloc(size_t size);
int syscall_clone(void);
void syscall_exit(void);
void syscall_write(const char *buf);
void syscall_cdelay(unsigned long cycles);
#endif // !__ASSEMBLER__

#define SYSCALL_ALLOC_NUM 0
#define SYSCALL_CLONE_NUM 1
#define SYSCALL_EXIT_NUM 2
#define SYSCALL_WRITE_NUM 3
#define SYSCALL_CDELAY_NUM 4

#define SYSCALL_MAX SYSCALL_CDELAY_NUM

#endif // !UAPI_SYSCALL_H
