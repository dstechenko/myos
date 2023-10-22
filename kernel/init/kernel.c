// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/init/kernel.h>

#include <asm/delay.h>
#include <asm/irq.h>
#include <asm/memory-defs.h>
#include <asm/registers.h>
#include <asm/sections.h>

#include <drivers/irq.h>
#include <drivers/timer.h>

#include <kernel/core/build_info.h>
#include <kernel/core/config.h>
#include <kernel/logging/log.h>
#include <kernel/logging/print.h>
#include <kernel/memory/page.h>
#include <kernel/scheduler/fork.h>
#include <kernel/scheduler/task.h>
#include <kernel/util/assert.h>
#include <kernel/util/ptrs.h>
#include <uapi/bool.h>

SECTION_LABEL(section_user_start);
SECTION_LABEL(section_user_end);
SECTION_LABEL(user_start);

void kernel_task(void) {
  int err;
  uintptr_t user_start_addr = SECTION_ADR(user_start);
  uintptr_t section_user_start_addr = SECTION_ADR(section_user_start);
  uintptr_t section_user_end_addr = SECTION_ADR(section_user_end);
  size_t section_user_size = (section_user_end_addr - section_user_start_addr);

  ASSERT(section_user_end_addr > section_user_start_addr);
  err = task_move_to_user(user_start_addr, section_user_start_addr, section_user_size);
  if (err)
    LOG_ERROR("Failed to move to user: %d", err);
}

void kernel_start(void) {
  int err;

  page_init();
  print_init();
  task_main_init();
  irq_init();
  timer_init();
  irq_ctrl_init();
  irq_enable();

  LOG_INFO("Booting kernel...");
  LOG_DEBUG("Kernel build info:");
  LOG_DEBUG("  Commit hash  - %s", BUILD_INFO_COMMIT_HASH);
  LOG_DEBUG("  Timestamp    - %s", BUILD_INFO_TIMESTAMP);
  LOG_DEBUG("  Target arch  - %s", BUILD_INFO_TARGET_ARCH);
  LOG_DEBUG("  Target board - %s", BUILD_INFO_TARGET_BOARD);
  LOG_DEBUG("  Target mode  - %s", BUILD_INFO_TARGET_MODE);
  LOG_DEBUG("  Host arch    - %s", BUILD_INFO_HOST_ARCH);

  sections_debug();
  page_debug(/* limit = */ 3);

  err = fork_task(REF_TO_ADR(kernel_task), FORK_KERNEL);
  if (err < 0) {
    LOG_ERROR("Failed to start task before user, err: %d", err);
    return;
  }

  while (true) {
    print("* Tick from kernel init task\n");
    cdelay(50000000);
    task_schedule();
  }
}
