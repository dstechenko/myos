// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_DELAY_H
#define KERNEL_DELAY_H

void cdelay(unsigned long cycles);
void udelay(unsigned long micros);
void mdelay(unsigned long millis);

#endif // !KERNEL_DELAY_H
