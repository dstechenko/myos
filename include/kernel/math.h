// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_MATH_H
#define KERNEL_MATH_H

static inline double fmod(const double a, const double b) {
  return (a / b) - ((long)(a / b));
}

#endif // !KERNEL_MATH_H
