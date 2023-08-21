// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_CORE_SYSCALL_H
#define KERNEL_CORE_SYSCALL_H

#include <stddef.h>
#include <stdint.h>

uintptr_t syscall_alloc(size_t size);
uintptr_t syscall_alloc_invoke(size_t size);

int syscall_clone(uintptr_t sp);
int syscall_clone_invoke(uintptr_t pc, uintptr_t sp);

void syscall_exit(void);
void syscall_exit_invoke(void);

void syscall_write(const char *buf);
void syscall_write_invoke(const char *buf);

#endif // !KERNEL_CORE_SYSCALL_H
