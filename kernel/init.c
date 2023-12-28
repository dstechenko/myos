// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/atomic.h>
#include <asm/delay.h>
#include <asm/irq.h>
#include <asm/memory-defs.h>
#include <asm/registers.h>
#include <asm/sections.h>

#include <drivers/random.h>
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

#include <uapi/bool.h>

SECTIONS(section_user);
SECTIONS(user);

static void kernel_task(void) {
  int err;

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
  page_debug(/* limit = */ 3);
  LOG_DEBUG("Random value sampled: %d", random_get(1, 100));
  LOG_DEBUG("Random value sampled: %d", random_get(1, 100));
  LOG_DEBUG("Random value sampled: %d", random_get(1, 100));
  atomic32_t x = ATOMIC_INIT(42);
  atomic32_inc(&x);
  LOG_DEBUG("Atomic value: %d", x.value);
  int32_t old = atomic32_cmp_swp(&x, 43, 40);
  LOG_DEBUG("Atomic new value: %d, old value: %d", x.value, old);
  old = atomic32_cmp_swp(&x, 41, 42);
  LOG_DEBUG("Atomic new value: %d, old value: %d", x.value, old);
}

static void init_start_user(void) { ASSERT(fork_task(REF_TO_ADR(kernel_task), FORK_KERNEL)); }

static void init_loop_schedule(void) {
  while (true) {
    delay_cycles(50000000);
    print("* Tick from kernel init task on core %d\n", registers_get_core());
    if (cpu_is_primary()) {
      task_schedule();
    }
  }
}

void init_start(void) {
  if (cpu_is_primary()) {
    sections_init();
    local_irq_init();
    print_init();
    page_init();
    task_main_init();
    subsystem_init();
    init_debug();
    init_start_user();
  }
  local_irq_init();
  local_irq_enable();
  init_loop_schedule();
}
