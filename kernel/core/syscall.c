// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/core/syscall.h>

#include <kernel/logging/log.h>
#include <kernel/memory/allocator.h>
#include <kernel/scheduler/fork.h>
#include <kernel/scheduler/task.h>

void *const syscall_table[] = {
    syscall_alloc,
    syscall_clone,
    syscall_exit,
    syscall_write,
};

uintptr_t syscall_alloc(const size_t size) { return (uintptr_t)alloc(size, ALLOC_USER); }

int syscall_clone(const uintptr_t sp) { return fork_task((uintptr_t)NULL, sp, FORK_USER); }

void syscall_exit(void) { task_exit(); }

void syscall_write(const char *buf) { LOG_INFO("%s", buf); }
