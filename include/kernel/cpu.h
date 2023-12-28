// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_CPU_H
#define KERNEL_CPU_H

#include <asm/registers.h>

#include <kernel/task.h>
#include <kernel/types.h>
#include <kernel/config.h>

#define DEFINE_PER_CPU(type, name) \
  static type name[CONFIG_BOOT_CPU_COUNT]

#define cpu_get_var(name)      \
({                             \
  task_preempt_disable();      \
  &name[registers_get_core()]; \
})

#define cpu_put_var(name)  \
do {                       \
  (void)name;              \
  task_preempt_enable();   \
} while(false)


bool cpu_is_primary(void);

#endif // !KERNEL_CPU_H
