// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/core/syscall.h>

#include <stddef.h>
#include <stdint.h>

#include <asm/delay.h>

#include <kernel/logging/print.h>
#include <kernel/memory/allocator.h>
#include <kernel/scheduler/fork.h>
#include <kernel/scheduler/task.h>

void *const syscall_table[] = {
    syscall_alloc, syscall_clone, syscall_exit, syscall_write, syscall_cdelay,
};

uintptr_t syscall_alloc(const size_t size) { return (uintptr_t)alloc(size, ALLOC_USER); }

int syscall_clone(void) { return fork_task((uintptr_t)NULL, FORK_USER); }

void syscall_exit(void) { task_exit(); }

void syscall_write(const char *buf) { print(buf); }

void syscall_cdelay(const unsigned long cycles) { cdelay(cycles); }
