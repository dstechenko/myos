// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/delay.h>
#include <asm/irq.h>
#include <asm/memory-defs.h>
#include <asm/registers.h>
#include <asm/sections.h>

#include <drivers/subsystem.h>

#include <kernel/assert.h>
#include <kernel/build-info.h>
#include <kernel/config.h>
#include <kernel/fork.h>
#include <kernel/log.h>
#include <kernel/page.h>
#include <kernel/print.h>
#include <kernel/ptrs.h>
#include <kernel/task.h>

#include <uapi/bool.h>

SECTION_LABEL(section_user_start);
SECTION_LABEL(section_user_end);
SECTION_LABEL(user_start);

static void kernel_task(void) {
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

static void kernel_pre_init(void) {
  print_init();
  local_irq_init();
  page_init();
  task_main_init();
}

static void kernel_post_init(void) { local_irq_enable(); }

static void init_schedule(void) {
  while (true) {
    print("* Tick from kernel init task on core %d\n", registers_get_core());
    cdelay(50000000);
    task_schedule();
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
  page_debug(/* limit = */ 3);
}

static void init_user(void) {
  ASSERT(fork_task(REF_TO_ADR(kernel_task), FORK_KERNEL));
}

void init_start(void) {
  kernel_pre_init();
  subsystem_init();
  kernel_post_init();
  init_debug();
  init_user();
  init_schedule();
}
