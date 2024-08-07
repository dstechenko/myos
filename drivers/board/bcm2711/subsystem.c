// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <drivers/cpu.h>
#include <drivers/subsystem.h>

#include "irq.h"
#include "random.h"
#include "timer.h"

void subsystem_init(void) {
  timer_init();
  irq_ctrl_init();
  random_init();
  cpu_init();
}
