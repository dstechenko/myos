// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "mmio.h"

#include <drivers/mmio.h>

#include <kernel/page.h>
#include <kernel/ptrs.h>

#define MMIO_REG(reg) (phys_to_virt(PTR_TO_ADR(MMIO_BASE) + reg))

void mmio_write8(const uintptr_t reg, const uint8_t data) { *(volatile uint8_t *)(MMIO_REG(reg)) = data; }

void mmio_write16(const uintptr_t reg, const uint16_t data) { *(volatile uint16_t *)(MMIO_REG(reg)) = data; }

void mmio_write32(const uintptr_t reg, const uint32_t data) { *(volatile uint32_t *)(MMIO_REG(reg)) = data; }

void mmio_write64(const uintptr_t reg, const uint64_t data) { *(volatile uint64_t *)(MMIO_REG(reg)) = data; }

uint8_t mmio_read8(const uintptr_t reg) { return *(volatile uint8_t *)(MMIO_REG(reg)); }

uint16_t mmio_read16(const uintptr_t reg) { return *(volatile uint16_t *)(MMIO_REG(reg)); }

uint32_t mmio_read32(const uintptr_t reg) { return *(volatile uint32_t *)(MMIO_REG(reg)); }

uint64_t mmio_read64(const uintptr_t reg) { return *(volatile uint64_t *)(MMIO_REG(reg)); }
