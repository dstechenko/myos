// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

void syscall_clone(void) {}

void syscall_exit(void) {}

void *syscall_table[] = {syscall_clone, syscall_exit};
