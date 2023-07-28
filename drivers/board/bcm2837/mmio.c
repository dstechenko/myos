// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <drivers/mmio.h>

#include <mmio_base.h>

void mmio_write8(uint32_t reg, uint8_t data)
{
	*(volatile uint8_t *)((uintptr_t)MMIO_BASE + reg) = data;
}

void mmio_write16(uint32_t reg, uint16_t data)
{
	*(volatile uint16_t *)((uintptr_t)MMIO_BASE + reg) = data;
}

void mmio_write32(uint32_t reg, uint32_t data)
{
	*(volatile uint32_t *)((uintptr_t)MMIO_BASE + reg) = data;
}

void mmio_write64(uint32_t reg, uint64_t data)
{
	*(volatile uint64_t *)((uintptr_t)MMIO_BASE + reg) = data;
}

uint8_t mmio_read8(uint32_t reg)
{
	return *(volatile uint8_t *)((uintptr_t)MMIO_BASE + reg);
}

uint16_t mmio_read16(uint32_t reg)
{
	return *(volatile uint16_t *)((uintptr_t)MMIO_BASE + reg);
}

uint32_t mmio_read32(uint32_t reg)
{
	return *(volatile uint32_t *)((uintptr_t)MMIO_BASE + reg);
}

uint64_t mmio_read64(uint32_t reg)
{
	return *(volatile uint64_t *)((uintptr_t)MMIO_BASE + reg);
}
