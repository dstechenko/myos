// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/delay.h>
#include <asm/irq.h>
#include <asm/registers.h>
#include <asm/sections.h>

#include <drivers/subsystem.h>
#include <drivers/uart.h>

#include <kernel/assert.h>
#include <kernel/build-info.h>
#include <kernel/config.h>
#include <kernel/cpu.h>
#include <kernel/fork.h>
#include <kernel/log.h>
#include <kernel/page.h>
#include <kernel/print.h>
#include <kernel/ptrs.h>
#include <kernel/task.h>
#include <kernel/test.h>
#include <kernel/types.h>

SECTIONS(section_user);
SECTIONS(user);

static void kernel_task(void) {
  int err;

  LOG_INFO("Forked kernel task!");

  ASSERT(SECTIONS_LENGTH(section_user));
  err = task_move_to_user(SECTIONS_START(user), SECTIONS_START(section_user), SECTIONS_LENGTH(section_user));
  if (err) {
    LOG_ERROR("Failed to move to user: %d", err);
  }
}

static void init_debug(void) {
  LOG_INFO("Booting kernel...");
  LOG_DEBUG("Kernel build info:");
  LOG_DEBUG("  Commit hash  - %s", BUILD_INFO_COMMIT_HASH);
  LOG_DEBUG("  Timestamp    - %s", BUILD_INFO_TIMESTAMP);
  LOG_DEBUG("  Target arch  - %s", BUILD_INFO_TARGET_ARCH);
  LOG_DEBUG("  Target board - %s", BUILD_INFO_TARGET_BOARD);
  LOG_DEBUG("  Target mode  - %s", BUILD_INFO_TARGET_MODE);
  LOG_DEBUG("  Host arch    - %s", BUILD_INFO_HOST_ARCH);
  sections_debug();
  page_debug(/* limit = */ 1);
}

static void init_start_user(void) { ASSERT(fork_task(REF_TO_ADR(kernel_task), FORK_KERNEL)); }

static void init_loop_schedule(void) {
  while (true) {
    delay_cycles(5000000);
    print("* Tick from kernel init task on core %d\n\r", registers_get_core());
    if (cpu_is_primary()) {
      task_schedule();
    }
  }
}

void init_start(void) {
  irq_local_init();
  irq_local_enable();

  if (cpu_is_primary()) {
    sections_init();
    print_init();
    page_init();
    task_main_init();
    subsystem_init();
    init_debug();
    init_start_user();
  }

#if CONFIG_ENABLED(CONFIG_KERNEL_TEST_ON_BOOT)
  if (cpu_is_primary()) {
    LOG_INFO("Testing...");
    test_all();
    LOG_INFO("Tested successfully!");
  }
#endif  // CONFIG_ENABLED(CONFIG_KERNEL_TEST_ON_BOOT)

  init_loop_schedule();
}
