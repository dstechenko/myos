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

static uintptr_t syscall_alloc_shim(const size_t size) { return PTR_TO_ADR(alloc(size, ALLOC_USER)); }

static int syscall_clone_shim(void) { return fork_task(PTR_TO_ADR(NULL), FORK_USER); }

static void syscall_exit_shim(void) { task_exit(); }

static void syscall_write_shim(const char *buf) { print(buf); }

static void syscall_cdelay_shim(const unsigned long cycles) { cdelay(cycles); }

void *const syscall_table[] = {
    syscall_alloc_shim, syscall_clone_shim, syscall_exit_shim, syscall_write_shim, syscall_cdelay_shim,
};
