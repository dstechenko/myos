// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/memory-defs.h>
#include <asm/mmu-defs.h>
#include <asm/page-defs.h>
#include <asm/sections.h>
#include <kernel/types.h>

static uintptr_t boot_page_index = PHYSICAL_DEVICE_MEMORY_START;

uintptr_t boot_user_pgd;
uintptr_t boot_kernel_pgd;

static void boot_memzero(uint8_t *dst, size_t cnt) {
  while (cnt > 0) {
    dst[--cnt] = 0;
  }
}

static uintptr_t boot_get_next_page(void) {
  uintptr_t page;

  boot_page_index -= PAGE_SIZE;
  page = boot_page_index;
  boot_memzero(page, PAGE_SIZE);

  return page;
}

static size_t boot_get_table_index(const size_t shift, const uintptr_t addr) {
  return (addr >> shift) & (PAGES_PER_TABLE - 1);
}

static uintptr_t boot_map_table(uintptr_t *table, const size_t shift, const uintptr_t addr) {
  uintptr_t page;
  size_t index;

  index = boot_get_table_index(shift, addr);
  if (table[index]) {
    return table[index] & PAGE_MASK;
  } else {
    page = boot_get_next_page();
    table[index] = page | MMU_TYPE_PAGE_TABLE;
    return page;
  }
}

static void boot_map_block(uintptr_t *table, const uintptr_t addr, const uint64_t flags) {
  size_t index;

  index = boot_get_table_index(SECTION_SHIFT, addr);
  table[index] = addr | flags;
}

static void boot_map_page(const uintptr_t pgd, const uintptr_t addr, const uint64_t flags) {
  uintptr_t pud, pmd, pte;

  pud = boot_map_table(pgd, PGD_SHIFT, addr);
  pmd = boot_map_table(pud, PUD_SHIFT, addr);

  boot_map_block(pmd, addr, flags);
}

static void boot_map_range(const uintptr_t pgd, uintptr_t begin, const uintptr_t end, const uint64_t flags) {
  while (begin < end) {
    boot_map_page(pgd, begin, flags);
    begin += PAGE_SIZE;
  }
}

void boot_create_page_tables(void) {
  uintptr_t pgd;

  // TODO(dstechenko): only map parts for boot, use flags

  pgd = boot_get_next_page();
  boot_map_range(pgd, PHYSICAL_MEMORY_START, 10 * SECTION_SIZE, MMU_KERNEL_FLAGS);
  boot_user_pgd = pgd;

  pgd = boot_get_next_page();
  boot_map_range(pgd, PHYSICAL_MEMORY_START, PHYSICAL_DEVICE_MEMORY_START, MMU_KERNEL_FLAGS);
  boot_map_range(pgd, PHYSICAL_DEVICE_MEMORY_START, PHYSICAL_DEVICE_MEMORY_END, MMU_DEVICE_FLAGS);
  boot_map_range(pgd, PHYSICAL_DEVICE_MEMORY_END, PHYSICAL_MEMORY_END, MMU_KERNEL_FLAGS);
  boot_kernel_pgd = pgd;
}
