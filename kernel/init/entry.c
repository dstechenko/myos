// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/init/entry.h>

#include <asm/irq.h>
#include <asm/regs.h>
#include <drivers/irq.h>
#include <drivers/timer.h>
#include <kernel/build_info.h>
#include <kernel/config.h>
#include <kernel/log.h>
#include <kernel/util/assert.h>

void kernel_entry(void) {
  log_init();
  irq_init();
  timer_init();
  irq_ctrl_init();
  irq_enable();

  log_info("MyOS boot complete!");
  log_info(">");
  log_info("Core privilege:      %d", regs_get_priv());
  log_info(">");
  log_info("Build commit hash:   %s", BUILD_INFO_COMMIT_HASH);
  log_info("Build timestamp:     %s", BUILD_INFO_TIMESTAMP);
  log_info("Build target arch:   %s", BUILD_INFO_TARGET_ARCH);
  log_info("Build target board:  %s", BUILD_INFO_TARGET_BOARD);
  log_info("Build target mode:   %s", BUILD_INFO_TARGET_MODE);
  log_info("Build host arch:     %s", BUILD_INFO_HOST_ARCH);
  log_info(">");
  log_debug("Logging test:");
  log_debug("%c", 'c');
  log_debug("%d", 123);
  log_debug("%o", 123);
  log_debug("%x", 123);
  log_info("Spinning now...");
  ASSERT(1 > 2);

  log_error("Should be unreachable");
}
