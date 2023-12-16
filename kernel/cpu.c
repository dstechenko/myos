// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/config.h>
#include <kernel/cpu.h>

#include <asm/registers.h>

bool cpu_is_primary(void) { return registers_get_core() == CONFIG_BOOT_PRIMARY_CPU_INDEX; }
