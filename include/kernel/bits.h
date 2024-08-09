// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_BITS_H
#define KERNEL_BITS_H

#ifdef __ASSEMBLER__
#define BIT(b) (1 << (b))
#define NOBIT(b) (0 << (b))
#else // !__ASSEMBLER__
#define BIT(b) (1UL << (b))
#define NOBIT(b) (0UL << (b))
#endif // __ASSEMBLER__

#define MASK_LOW_HALF_BYTE(b) ((b)&0x0F)
#define MASK_HIGH_HALF_BYTE(b) ((b)&0xF0)

#define MASK_LOW_BYTE(w) ((w)&0x00FF)
#define MASK_HIGH_BYTE(w) ((w)&0xFF00)

#define MASK_LOW_WORD(dw) ((dw)&0x0000FFFF)
#define MASK_HIGH_WORD(dw) ((dw)&0xFFFF0000)

#define SELECT_BIT(v, i) (((v) & BIT(i)) >> (i))
#define SELECT_BITS(v, i, b) (((v) & (b)) >> (i))

#endif // !KERNEL_BITS_H
