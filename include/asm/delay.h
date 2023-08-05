// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ASM_DELAY_H
#define ASM_DELAY_H

void cdelay(unsigned long cycles);
void udelay(unsigned long micros);
void mdelay(unsigned long millis);

#endif // !ASM_DELAY_H
