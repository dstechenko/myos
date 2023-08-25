// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ARCH_AARCH64_ASM_MMU_H
#define ARCH_AARCH64_ASM_MMU_H
#ifndef __ASSEMBLER__

#include <stdint.h>

void handle_data_abort(uint64_t far, uint64_t esr);

#endif // !__ASSEMBLER__
#endif // !ARCH_AARCH64_ASM_MMU_H
