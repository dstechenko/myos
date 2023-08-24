// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_UTIL_MATH_H
#define KERNEL_UTIL_MATH_H

static inline int abs(int value) { return value >= 0 ? value : -value; }

static inline long labs(long value) { return value >= 0 ? value : -value; }

static inline long long llabs(long long value) { return value >= 0 ? value : -value; }

#endif // !KERNEL_UTIL_MATH_H
