// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef DRIVERS_TIMER_H
#define DRIVERS_TIMER_H

#include <stdint.h>

void timer_handle(void);
uint64_t timer_get_ticks(void);

#endif // !DRIVERS_TIMER_H
