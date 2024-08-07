// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/atomic.h>
#include <asm/cpu.h>
#include <asm/delay.h>
#include <asm/irq.h>
#include <asm/sections.h>

#include <drivers/subsystem.h>

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

  ASSERT(SECTIONS_LENGTH(section_user));
  err = task_move_to_user(SECTIONS_START(user), SECTIONS_START(section_user), SECTIONS_LENGTH(section_user));
  if (err) {
    LOG_ERROR("Failed to spin a user task, err: %d", err);
  }
}

static void init_user(void) {
  ASSERT(fork_task(REF_TO_ADR(kernel_task), FORK_KERNEL));
  LOG_DEBUG("User init OK", cpu_get_core());
}

static void init_report(void) {
  if (cpu_is_primary()) {
    LOG_DEBUG("Build info:");
    LOG_DEBUG("  Commit hash  - %s", BUILD_INFO_COMMIT_HASH);
    LOG_DEBUG("  Timestamp    - %s", BUILD_INFO_TIMESTAMP);
    LOG_DEBUG("  Target arch  - %s", BUILD_INFO_TARGET_ARCH);
    LOG_DEBUG("  Target board - %s", BUILD_INFO_TARGET_BOARD);
    LOG_DEBUG("  Target mode  - %s", BUILD_INFO_TARGET_MODE);
    LOG_DEBUG("  Host arch    - %s", BUILD_INFO_HOST_ARCH);
    sections_debug();
  } else {
    delay_cycles(1000000000);
  }
  LOG_INFO("Kernel init OK [core %d]", cpu_get_core());
}

void init_loop_forever(void) {
  while (true) {
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
    task_init_main();
    subsystem_init();
    init_user();
    test_init();
  }

  init_report();
  init_loop_forever();
}
