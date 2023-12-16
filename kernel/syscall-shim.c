// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <stddef.h>
#include <stdint.h>

#include <asm/delay.h>

#include <kernel/allocator.h>
#include <kernel/fork.h>
#include <kernel/print.h>
#include <kernel/ptrs.h>
#include <kernel/task.h>

#include <uapi/syscall.h>

static uintptr_t syscall_alloc_shim(const size_t size) { return PTR_TO_ADR(alloc(size, ALLOC_USER)); }

static int syscall_clone_shim(void) { return fork_task(PTR_TO_ADR(NULL), FORK_USER); }

static void syscall_exit_shim(void) { task_exit(); }

static void syscall_write_shim(const char *buf) { print(buf); }

static void syscall_delay_shim(const unsigned long cycles) { delay_cycles(cycles); }

void *const syscall_table[] = {
    [SYSCALL_ALLOC_NUM] = syscall_alloc_shim, [SYSCALL_CLONE_NUM] = syscall_clone_shim,
    [SYSCALL_EXIT_NUM] = syscall_exit_shim,   [SYSCALL_WRITE_NUM] = syscall_write_shim,
    [SYSCALL_DELAY_NUM] = syscall_delay_shim,
};
