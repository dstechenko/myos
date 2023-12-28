// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/barrier.h>

void barrier_compiler(void) { asm volatile("" ::: "memory"); }
