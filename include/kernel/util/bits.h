// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_UTIL_BITS_H
#define KERNEL_UTIL_BITS_H

#define BIT(b) (1 << b)
#define NOBIT(b) (0 << b)

#define MASK_LOW_HALF_BYTE(b) (b & 0x0F)
#define MASK_HIGH_HALF_BYTE(b) (b & 0xF0)

#define MASK_LOW_BYTE(w) (w & 0x00FF)
#define MASK_HIGH_BYTE(w) (w & 0xFF00)

#define MASK_LOW_WORD(dw) (dw & 0x0000FFFF)
#define MASK_HIGH_WORD(dw) (dw & 0xFFFF0000)

#endif // !KERNEL_UTIL_BITS_H
