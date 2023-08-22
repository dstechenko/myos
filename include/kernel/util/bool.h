// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_UTIL_BOOL_H
#define KERNEL_UTIL_BOOL_H

#define true 1
#define false 0

#ifndef __ASSEMBLER__
typedef _Bool bool;
#endif // !__ASSEMBLER__

#endif // !KERNEL_UTIL_BOOL_H
