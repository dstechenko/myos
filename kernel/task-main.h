// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_TASK_MAIN_H
#define KERNEL_TASK_MAIN_H

#include <stddef.h>

#include <kernel/config.h>
#include <kernel/task.h>

#define INIT_TASK_MAIN(task)                                                                       \
  {                                                                                                \
    .id = 0, .context = NULL, .state = TASK_RUNNING, .ticks = 0,                                   \
    .priority = CONFIG_KERNEL_SCHEDULER_PRIORITY, .preempt = 0,                                    \
  }

#endif // !KERNEL_TASK_MAIN_H
