// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_SCHEDULER_FORK_H
#define KERNEL_SCHEDULER_FORK_H

int fork(const void *func);
void fork_return(void);

#endif // !KERNEL_SCHEDULER_FORK_H
