// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ARCH_AARCH64_ASM_TYPES_H
#define ARCH_AARCH64_ASM_TYPES_H

#define TYPES_CONCAT(left, right) left##right
#define TYPES_MEMORY(addr) TYPES_CONCAT(addr, ull)

#endif  // !ARCH_AARCH64_ASM_TYPES_H
