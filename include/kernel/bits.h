// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef MYOS_KERNEL_BITS_H
#define MYOS_KERNEL_BITS_H

#include <stdint.h>

#define MASK_LOW_HALF_BYTE(b)  (b & 0x0F)
#define MASK_HIGH_HALF_BYTE(b) (b & 0xF0)

#define MASK_LOW_BYTE(w)  (w & 0x00FF)
#define MASK_HIGH_BYTE(w) (w & 0xFF00)

#define MASK_LOW_WORD(dw)  (dw & 0x0000FFFF)
#define MASK_HIGH_WORD(dw) (dw & 0xFFFF0000)

#define LOW_HALF_BYTE(b)  ((uint8_t)MASK_LOW_HALF_BYTE(b))
#define HIGH_HALF_BYTE(b) ((LOW_HALF_BYTE(b >> 4)))

#define LOW_BYTE(w)  ((uint8_t)MASK_LOW_BYTE(w))
#define HIGH_BYTE(w) ((LOW_BYTE(w >> 8)))

#define LOW_WORD(dw)  ((uint16_t)MASK_LOW_WORD(dw))
#define HIGH_WORD(dw) ((LOW_WORD(dw >> 16)))

#endif // !MYOS_KERNEL_BITS_H
