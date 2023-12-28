// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef DRIVERS_BOARD_BCM2837_TIMER_H
#define DRIVERS_BOARD_BCM2837_TIMER_H

#include <kernel/bits.h>

/**
 * The  base address for the system timers is 0x7E003000.
 *
 * The System Timer peripheral provides four 32-bit timer channels and a single
 * 64-bit free running counter. Each channel has an output compare register,
 * which is compared against the 32 least significant bits of the free running
 * counter values. When the two values match, the system timer peripheral
 * generates a signal to indicate a match for the appropriate channel. The match
 * signal is then fed into the interrupt controller. The interrupt service
 * routine then reads the output compare register and adds the appropriate
 * offset for the next timer tick. The free running counter is driven by the
 * timer clock and stopped whenever the processor is stopped in debug mode.
 */

#define TIMER_BASE 0x00003000

#define TIMER_CS (TIMER_BASE + 0x00)
#define TIMER_CLO (TIMER_BASE + 0x04)
#define TIMER_CHI (TIMER_BASE + 0x08)
#define TIMER_C0 (TIMER_BASE + 0x0C)
#define TIMER_C1 (TIMER_BASE + 0x10)
#define TIMER_C2 (TIMER_BASE + 0x14)
#define TIMER_C3 (TIMER_BASE + 0x18)

#define TIMER_CS_M0 BIT(0)
#define TIMER_CS_M1 BIT(1)
#define TIMER_CS_M2 BIT(2)
#define TIMER_CS_M3 BIT(3)

void timer_init(void);
void timer_handle(void);

#endif // !DRIVERS_BOARD_BCM2837_TIMER_H
