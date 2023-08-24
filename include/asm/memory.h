// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_MEMORY_H
#define ASM_MEMORY_H

#include <kernel/core/config.h>

#define PHYSICAL_MEMORY_START CONFIG_PHYSICAL_MEMORY_START
#define PHYSICAL_MEMORY_END CONFIG_PHYSICAL_MEMORY_END
#define PHYSICAL_MEMORY_SIZE (PHYSICAL_MEMORY_END - PHYSICAL_MEMORY_START)

#define PHYSICAL_DEVICE_MEMORY_START CONFIG_PHYSICAL_DEVICE_MEMORY_START
#define PHYSICAL_DEVICE_MEMORY_END CONFIG_PHYSICAL_DEVICE_MEMORY_END
#define PHYSICAL_DEVICE_MEMORY_SIZE (PHYSICAL_DEVICE_MEMORY_END - PHYSICAL_DEVICE_MEMORY_START)

#define VIRTUAL_MEMORY_START CONFIG_VIRTUAL_MEMORY_OFFSET
#define VIRTUAL_MEMORY_END (VIRTUAL_MEMORY_START + PHYSICAL_MEMORY_SIZE)
#define VIRTUAL_MEMORY_SIZE PHYSICAL_MEMORY_SIZE

#define VIRTUAL_DEVICE_MEMORY_START (VIRTUAL_MEMORY_START + PHYSICAL_DEVICE_MEMORY_START)
#define VIRTUAL_DEVICE_MEMORY_END (VIRTUAL_DEVICE_MEMORY_START + PHYSICAL_DEVICE_MEMORY_SIZE)
#define VIRTUAL_DEVICE_MEMORY_SIZE PHYSICAL_MEMORY_SIZE

#ifndef __ASSEMBLER__
#endif // !__ASSEMBLER__

#endif // !ASM_MEMORY_H
