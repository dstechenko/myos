// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef DRIVERS_MMIO_H
#define DRIVERS_MMIO_H

#include <stdint.h>

// TODO(dstechenk): no hardcoding for address

void mmio_write8(uint64_t reg, uint8_t data);
void mmio_write16(uint64_t reg, uint16_t data);
void mmio_write32(uint64_t reg, uint32_t data);
void mmio_write64(uint64_t reg, uint64_t data);

uint8_t mmio_read8(uint64_t reg);
uint16_t mmio_read16(uint64_t reg);
uint32_t mmio_read32(uint64_t reg);
uint64_t mmio_read64(uint64_t reg);

#endif // !DRIVERS_MMIO_H
