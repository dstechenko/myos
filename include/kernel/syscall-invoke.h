// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_SYSCALL_H
#define KERNEL_SYSCALL_H

#include <stddef.h>
#include <stdint.h>

uintptr_t syscall_alloc_invoke(size_t size);
int syscall_clone_invoke(void);
void syscall_exit_invoke(void);
void syscall_write_invoke(const char *buf);
void syscall_delay_cycles_invoke(unsigned long cycles);

#endif // !KERNEL_SYSCALL_H
