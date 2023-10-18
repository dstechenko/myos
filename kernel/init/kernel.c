// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/init/kernel.h>

#include <asm/delay.h>
#include <asm/irq.h>
#include <asm/memory-defs.h>
#include <asm/registers.h>
#include <drivers/irq.h>
#include <drivers/timer.h>
#include <kernel/core/build_info.h>
#include <kernel/core/config.h>
#include <kernel/core/syscall.h>
#include <kernel/logging/log.h>
#include <kernel/logging/print.h>
#include <kernel/memory/page.h>
#include <kernel/scheduler/fork.h>
#include <kernel/scheduler/task.h>

void task_a(void) {
  while (true) {
    LOG_INFO("tick from task a");
    cdelay(50000000);
  }
}

void task_b(void) {
  while (true) {
    LOG_INFO("tick from task b");
    cdelay(50000000);
  }
}

void task_user(void) {
  int err;
  uintptr_t stack;

  syscall_write_invoke("tick from task in user");

  stack = syscall_alloc_invoke(CONFIG_KERNEL_SCHEDULER_STACK_SIZE);
  if (!stack) {
    LOG_ERROR("Failed to allocate user stack for task a");
    goto exit;
  }

  err = syscall_clone_invoke((uintptr_t)&task_a, stack);
  if (err < 0) {
    LOG_ERROR("Failed to clone user task a, err %d", err);
    goto exit;
  }

  stack = syscall_alloc_invoke(CONFIG_KERNEL_SCHEDULER_STACK_SIZE);
  if (!stack) {
    LOG_ERROR("Failed to allocate user stack for task b");
    goto exit;
  }

  err = syscall_clone_invoke((uintptr_t)&task_b, stack);
  if (err < 0) {
    LOG_ERROR("Failed to clone user task b, err %d", err);
    goto exit;
  }

exit:
  syscall_exit_invoke();
}

void task_kernel(void) {
  uintptr_t task_user_in_user = (uintptr_t)task_user - VIRTUAL_MEMORY_START;
  LOG_INFO("tick from task in kernel, priv %d", registers_get_priv());
  LOG_INFO("task in kernel addr %lx", &task_kernel);
  LOG_INFO("task in user addr %lx", task_user_in_user);
  task_move_to_user(task_user_in_user);
}

void kernel_start(void) {
  int err;

  print_init();
  task_main_init();
  irq_init();
  timer_init();
  irq_ctrl_init();
  irq_enable();

  LOG_INFO("");
  LOG_INFO("");
  LOG_INFO("MyOS boot started!");
  LOG_INFO("");
  LOG_INFO("Build commit hash:   %s", BUILD_INFO_COMMIT_HASH);
  LOG_INFO("Build timestamp:     %s", BUILD_INFO_TIMESTAMP);
  LOG_INFO("Build target arch:   %s", BUILD_INFO_TARGET_ARCH);
  LOG_INFO("Build target board:  %s", BUILD_INFO_TARGET_BOARD);
  LOG_INFO("Build target mode:   %s", BUILD_INFO_TARGET_MODE);
  LOG_INFO("Build host arch:     %s", BUILD_INFO_HOST_ARCH);
  LOG_INFO("");
  LOG_INFO("Physical memory start:        %lx", PHYSICAL_MEMORY_START);
  LOG_INFO("Physical memory end:          %lx", PHYSICAL_MEMORY_END);
  LOG_INFO("Physical memory size:         %lx", PHYSICAL_MEMORY_SIZE);
  LOG_INFO("Physical device memory start: %lx", PHYSICAL_DEVICE_MEMORY_START);
  LOG_INFO("Physical device memory end:   %lx", PHYSICAL_DEVICE_MEMORY_END);
  LOG_INFO("Physical device memory size:  %lx", PHYSICAL_DEVICE_MEMORY_SIZE);
  LOG_INFO("Virtual memory start:         %lx", VIRTUAL_MEMORY_START);
  LOG_INFO("Virtual memory end:           %lx", VIRTUAL_MEMORY_END);
  LOG_INFO("Virtual memory size:          %lx", VIRTUAL_MEMORY_SIZE);
  LOG_INFO("Virtual device memory start:  %lx", VIRTUAL_DEVICE_MEMORY_START);
  LOG_INFO("Virtual device memory end:    %lx", VIRTUAL_DEVICE_MEMORY_END);
  LOG_INFO("Virtual device memory size:   %lx", VIRTUAL_DEVICE_MEMORY_SIZE);
  LOG_INFO("Boot entry location:          %lx", BOOT_LOAD_ADDRESS);
  LOG_INFO("Kernel entry location:        %lx", &kernel_start);
  LOG_INFO("Kernel stack location:        %lx", &err);
  LOG_INFO("");
  LOG_INFO("");

  /* debug_pages(); */

  err = fork_task((uintptr_t)&task_kernel, (uintptr_t)NULL, FORK_KERNEL);
  if (err < 0) {
    LOG_ERROR("Failed to start task before user, err: %d", err);
    return;
  }

  while (true)
    task_schedule();
}
