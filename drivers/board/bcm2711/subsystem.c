// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <drivers/subsystem.h>

#include "cpu.h"
#include "irq.h"
#include "timer.h"

void subsystem_init(void) {
  timer_init();
  irq_init();
  cpu_init();
}
