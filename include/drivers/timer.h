// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef DRIVERS_TIMER_H
#define DRIVERS_TIMER_H

#include <kernel/types.h>

uint64_t timer_get_ticks(void);
void timer_debug(void);

#endif // !DRIVERS_TIMER_H
