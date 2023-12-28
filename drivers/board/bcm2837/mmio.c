// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <drivers/mmio.h>

#include "mmio.h"

void mmio_write8(const uint32_t reg, const uint8_t data) {
  *(volatile uint8_t *)((uintptr_t)MMIO_BASE + reg) = data;
}

void mmio_write16(const uint32_t reg, const uint16_t data) {
  *(volatile uint16_t *)((uintptr_t)MMIO_BASE + reg) = data;
}

void mmio_write32(const uint32_t reg, const uint32_t data) {
  *(volatile uint32_t *)((uintptr_t)MMIO_BASE + reg) = data;
}

void mmio_write64(const uint32_t reg, const uint64_t data) {
  *(volatile uint64_t *)((uintptr_t)MMIO_BASE + reg) = data;
}

uint8_t mmio_read8(const uint32_t reg) { return *(volatile uint8_t *)((uintptr_t)MMIO_BASE + reg); }

uint16_t mmio_read16(const uint32_t reg) {
  return *(volatile uint16_t *)((uintptr_t)MMIO_BASE + reg);
}

uint32_t mmio_read32(const uint32_t reg) {
  return *(volatile uint32_t *)((uintptr_t)MMIO_BASE + reg);
}

uint64_t mmio_read64(const uint32_t reg) {
  return *(volatile uint64_t *)((uintptr_t)MMIO_BASE + reg);
}
