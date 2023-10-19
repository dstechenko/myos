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
#include <kernel/util/bool.h>
#include <kernel/util/ptrs.h>

void kernel_task(void) {
  LOG_INFO("Run in kernel, priv %d", registers_get_priv());
  LOG_INFO("Current location %lx", &kernel_task);
  while (true) {
    LOG_INFO("Tick from kernel task");
    cdelay(50000000);
  }
}

SECTION_LABEL(section_text_start);

void kernel_start(void) {
  int err;

  print_init();
  task_main_init();
  irq_init();
  timer_init();
  irq_ctrl_init();
  irq_enable();

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
  LOG_INFO("Boot load location:           %lx", BOOT_LOAD_ADDRESS);
  LOG_INFO("Kernel start location:        %lx", SECTION_PTR(section_text_start));
  LOG_INFO("Kernel entry location:        %lx", REF_TO_ADR(kernel_start));
  LOG_INFO("Kernel stack location:        %lx", &err);
  LOG_INFO("");

  /* debug_pages(); */

  err = fork_task(REF_TO_ADR(kernel_task), FORK_KERNEL);
  if (err < 0) {
    LOG_ERROR("Failed to start task before user, err: %d", err);
    return;
  }

  while (true) {
    LOG_INFO("Tick from init task");
    cdelay(50000000);
    task_schedule();
  }
}
