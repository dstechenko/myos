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
#include <kernel/logging/log.h>
#include <kernel/scheduler/fork.h>
#include <kernel/scheduler/task.h>

static const char *messages[] = {"null", "hello"};
#define FORK_DELAY 50000000

void task_a(void) {
  while (true) {
    // LOG_INFO("tick from task a");
    cdelay(FORK_DELAY);
  }
}

void task_b(void) {
  while (true) {
    // LOG_INFO("tick from task b");
    cdelay(FORK_DELAY);
  }
}

void kernel_entry(void) {
  int err;

  log_init();
  task_init();
  irq_init();
  timer_init();
  irq_ctrl_init();
  irq_enable();

  LOG_INFO("MyOS boot complete!");
  /* LOG_INFO(">"); */
  /* LOG_INFO("Core privilege:      %d", regs_get_priv()); */
  /* LOG_INFO(">"); */
  /* LOG_INFO("Build commit hash:   %s", BUILD_INFO_COMMIT_HASH); */
  /* LOG_INFO("Build timestamp:     %s", BUILD_INFO_TIMESTAMP); */
  /* LOG_INFO("Build target arch:   %s", BUILD_INFO_TARGET_ARCH); */
  /* LOG_INFO("Build target board:  %s", BUILD_INFO_TARGET_BOARD); */
  /* LOG_INFO("Build target mode:   %s", BUILD_INFO_TARGET_MODE); */
  /* LOG_INFO("Build host arch:     %s", BUILD_INFO_HOST_ARCH); */
  /* LOG_INFO(">"); */
  /* LOG_DEBUG("Logging test:"); */
  /* LOG_DEBUG("%c", 'c'); */
  /* LOG_DEBUG("%d", 123); */
  /* LOG_DEBUG("%d", -123); */
  /* LOG_DEBUG("%o", 123); */
  /* LOG_DEBUG("%x", 123); */
  /* LOG_DEBUG("%s", messages[1]); */

  err = fork_task(&task_a);
  if (err) {
    LOG_ERROR("Failed to start task a, err: %d", -err);
    return;
  }

  err = fork_task(&task_b);
  if (err) {
    LOG_ERROR("Failed to start task b, err: %d", -err);
    return;
  }

  while (true)
    task_schedule();
}
