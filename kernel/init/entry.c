// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/init/entry.h>

#include <asm/delay.h>
#include <asm/irq.h>
#include <asm/regs.h>
#include <drivers/irq.h>
#include <drivers/timer.h>
#include <kernel/build_info.h>
#include <kernel/config.h>
#include <kernel/core/syscall.h>
#include <kernel/logging/log.h>
#include <kernel/scheduler/fork.h>
#include <kernel/scheduler/task.h>

static const char *messages[] = {"null", "hello"};
#define LOOP_DELAY 50000000

void task_a(void) {
  while (true) {
    LOG_INFO("tick from task a");
    cdelay(LOOP_DELAY);
  }
}

void task_b(void) {
  while (true) {
    LOG_INFO("tick from task b");
    cdelay(LOOP_DELAY);
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
  LOG_INFO("tick from task in kernel, priv %d", regs_get_priv());
  task_move_to_user((uintptr_t)&task_user);
}

void kernel_entry(void) {
  int err;

  log_init();
  task_main_init();
  irq_init();
  timer_init();
  irq_ctrl_init();
  irq_enable();

  LOG_INFO("MyOS boot complete!");
  LOG_INFO(">");
  LOG_INFO("Core privilege:      %d", regs_get_priv());
  LOG_INFO(">");
  LOG_INFO("Build commit hash:   %s", BUILD_INFO_COMMIT_HASH);
  LOG_INFO("Build timestamp:     %s", BUILD_INFO_TIMESTAMP);
  LOG_INFO("Build target arch:   %s", BUILD_INFO_TARGET_ARCH);
  LOG_INFO("Build target board:  %s", BUILD_INFO_TARGET_BOARD);
  LOG_INFO("Build target mode:   %s", BUILD_INFO_TARGET_MODE);
  LOG_INFO("Build host arch:     %s", BUILD_INFO_HOST_ARCH);
  LOG_INFO(">");
  LOG_DEBUG("Logging test:");
  LOG_DEBUG("%c", 'c');
  LOG_DEBUG("%d", 123);
  LOG_DEBUG("%d", -123);
  LOG_DEBUG("%o", 123);
  LOG_DEBUG("%x", 123);
  LOG_DEBUG("%s", messages[1]);

  err = fork_task(&task_kernel, NULL, FORK_KERNEL);
  if (err < 0) {
    LOG_ERROR("Failed to start task before user, err: %d", err);
    return;
  }

  while (true)
    task_schedule();
}
