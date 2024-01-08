// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/registers.h>
#include <kernel/config.h>
#include <kernel/cpu.h>

bool cpu_is_primary(void) { return registers_get_core() == CONFIG_BOOT_PRIMARY_CPU_INDEX; }
