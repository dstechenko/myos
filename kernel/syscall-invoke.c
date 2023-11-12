// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/syscall-invoke.h>

#include <stddef.h>
#include <stdint.h>

#include <asm/delay.h>

#include <kernel/allocator.h>
#include <kernel/fork.h>
#include <kernel/print.h>
#include <kernel/ptrs.h>
#include <kernel/task.h>

void *const syscall_table[] = {
    syscall_alloc_invoke, syscall_clone_invoke, syscall_exit_invoke, syscall_write_invoke, syscall_cdelay_invoke,
};

uintptr_t syscall_alloc_invoke(const size_t size) { return PTR_TO_ADR(alloc(size, ALLOC_USER)); }

int syscall_clone_invoke(void) { return fork_task(PTR_TO_ADR(NULL), FORK_USER); }

void syscall_exit_invoke(void) { task_exit(); }

void syscall_write_invoke(const char *buf) { print(buf); }

void syscall_cdelay_invoke(const unsigned long cycles) { cdelay(cycles); }
