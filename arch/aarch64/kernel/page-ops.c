// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "page-ops.h"

#include <asm/cpu.h>
#include <asm/memory-defs.h>
#include <asm/mmu-defs.h>
#include <asm/page-defs.h>
#include <asm/sections.h>

#include <kernel/assert.h>
#include <kernel/bits.h>
#include <kernel/log.h>
#include <kernel/memory-ops.h>
#include <kernel/ptrs.h>
#include <kernel/types.h>

#include "page-context.h"

#define GET_DESC_VALID_BIT(desc) (desc & BIT(0))
#define GET_DESC_TABLE_BIT(desc) (desc & BIT(1))
#define GET_DESC_ADDR_BITS(desc) (desc & (BIT(48) - 1) & ~(BIT(12) - 1))
#define GET_DESC_LOW_ATTR_BITS(desc) (desc & (BIT(12) - 1) & ~(BIT(2) - 1))

SECTIONS(section_kernel);
#define PHYSICAL_KERNEL_MEMORY_END virt_to_phys(SECTIONS_END(section_kernel))

static uintptr_t *phys_to_virt_array(const uintptr_t paddr) { return (uintptr_t *)phys_to_virt(paddr); }

static struct page phys_to_virt_page(const uintptr_t paddr) {
  return (struct page){.paddr = paddr, .vaddr = phys_to_virt(paddr)};
}

// TODO(dstechenko): fix memory_zero on pages

static void log_page_entries(const uintptr_t table, size_t limit) {
  uintptr_t *cursor = (uintptr_t *)table;
  size_t empty = 0, unseen = 0;

  ASSERT(cursor);

  for (size_t i = 0; i < PAGES_PER_TABLE; i++) {
    if (!cursor[i]) {
      empty++;
      continue;
    }

    if (limit && empty) {
      LOG_DEBUG("    ... %u empty entries ...", empty);
      empty = 0;
      limit--;
    }

    if (limit) {
      const bool is_valid = GET_DESC_VALID_BIT(cursor[i]);
      const bool is_table = GET_DESC_TABLE_BIT(cursor[i]);
      const uintptr_t addr = GET_DESC_ADDR_BITS(cursor[i]);
      const uint64_t flags = GET_DESC_LOW_ATTR_BITS(cursor[i]);

      LOG_DEBUG("    type=%s[%s] bits=%lx, addr=%lx, flags=%lx", is_table ? "table" : "block",
                is_valid ? "valid" : "invalid", cursor[i], addr, flags);
      limit--;
    } else {
      unseen++;
    }
  }

  if (unseen)
    LOG_DEBUG("    ... %u more entries ...", unseen);
  else if (empty)
    LOG_DEBUG("    ... %u empty entries ...", empty);
}

void log_page_global_directory(const uintptr_t pgd, const size_t limit) {
  uintptr_t *pud = phys_to_virt_array(pgd), *pmd, *pte;

  if (!pgd) return;

  LOG_DEBUG("  Page Global Directory (physical address %lx)", pgd);
  log_page_entries(phys_to_virt(pgd), limit);

  for (size_t i = 0; i < limit; i++)
    if (pud[i]) {
      LOG_DEBUG("  Page Upper Directory (physical address %lx)", GET_DESC_ADDR_BITS(pud[i]));
      log_page_entries(phys_to_virt(GET_DESC_ADDR_BITS(pud[i])), limit);
    }

  for (size_t i = 0; i < limit; i++)
    if (pud[i]) {
      pmd = phys_to_virt_array(GET_DESC_ADDR_BITS(pud[i]));
      for (size_t j = 0; j < limit; j++)
        if (pmd[j]) {
          LOG_DEBUG("  Page Middle Directory (physical address %lx)", GET_DESC_ADDR_BITS(pmd[j]));
          log_page_entries(phys_to_virt(GET_DESC_ADDR_BITS(pmd[j])), limit);
        }
    }

  for (size_t i = 0; i < limit; i++)
    if (pud[i]) {
      pmd = phys_to_virt_array(GET_DESC_ADDR_BITS(pud[i]));
      for (size_t j = 0; j < limit; j++)
        if (pmd[j]) {
          pte = phys_to_virt_array(GET_DESC_ADDR_BITS(pmd[j]));
          for (size_t k = 0; k < limit; k++)
            if (pte[k] && GET_DESC_TABLE_BIT(pte[k])) {
              LOG_DEBUG("  Page Table Entry (physical address %lx)", GET_DESC_ADDR_BITS(pte[k]));
              log_page_entries(phys_to_virt(GET_DESC_ADDR_BITS(pte[k])), limit);
            }
        }
    }
}

void page_debug(const size_t limit) {
  LOG_DEBUG("Memory configurations:");
  LOG_DEBUG("  Boot load address            - %lx", BOOT_LOAD_ADDRESS);
  LOG_DEBUG("  Physical memory start        - %lx", PHYSICAL_MEMORY_START);
  LOG_DEBUG("  Physical memory end:         - %lx", PHYSICAL_MEMORY_END);
  LOG_DEBUG("  Physical memory size:        - %lx", PHYSICAL_MEMORY_SIZE);
  LOG_DEBUG("  Physical device memory start - %lx", PHYSICAL_DEVICE_MEMORY_START);
  LOG_DEBUG("  Physical device memory end   - %lx", PHYSICAL_DEVICE_MEMORY_END);
  LOG_DEBUG("  Physical device memory size  - %lx", PHYSICAL_DEVICE_MEMORY_SIZE);
  LOG_DEBUG("User pages:");
  log_page_global_directory(cpu_get_user_pt(), limit);
  LOG_DEBUG("Kernel pages:");
  log_page_global_directory(cpu_get_kernel_pt(), limit);
}

void page_init_sections(void) {
  // TODO(dstechenko): re-use boot pages, move out page tables
  page_reserve_range(PHYSICAL_MEMORY_START, PHYSICAL_KERNEL_MEMORY_END);
  // TODO(dstechenko): do not assume page alignment on device memory
  page_reserve_range(PHYSICAL_DEVICE_MEMORY_START, PHYSICAL_DEVICE_MEMORY_END);
}

static size_t get_table_index(size_t shift, uintptr_t vaddr) {
  return (vaddr >> shift) & (PAGES_PER_TABLE - 1);
}

static uintptr_t map_table(uintptr_t *table, size_t shift, uintptr_t vaddr, bool *created) {
  uintptr_t ret;
  size_t index;

  ASSERT(table);
  ASSERT(created);

  index = get_table_index(shift, vaddr);
  if (table[index]) {
    *created = false;
    ret = table[index] & PAGE_MASK;
  } else {
    *created = true;
    uintptr_t next_table = page_alloc(/* order = */ 0, PF_KERNEL);
    memory_zero(phys_to_virt_array(next_table), PAGE_SIZE);
    table[index] = next_table | MMU_TYPE_PAGE_TABLE;
    ret = next_table;
  }

  return ret;
}

static void map_table_entry(uintptr_t *entry, struct page page, const uint64_t flags) {
  size_t index;

  ASSERT(entry);

  index = get_table_index(PAGE_SHIFT, page.vaddr);
  entry[index] = page.paddr | flags;
}

static void page_map_kernel_into(uintptr_t pgd, struct page page, const uint64_t flags) {
  bool created;
  uintptr_t pud, pmd, pte;

  pud = map_table(phys_to_virt_array(pgd), PGD_SHIFT, page.vaddr, &created);
  pmd = map_table(phys_to_virt_array(pud), PUD_SHIFT, page.vaddr, &created);
  pte = map_table(phys_to_virt_array(pmd), PMD_SHIFT, page.vaddr, &created);

  map_table_entry(phys_to_virt_array(pte), page, flags);
}

void page_map_kernel(struct page page) {
  page_map_kernel_into(cpu_get_kernel_pt(), page, MMU_KERNEL_PAGES_FLAGS);
  // TODO(dstechenko): just flash tlbs here instead
  cpu_set_kernel_pt(cpu_get_kernel_pt());
}

static void map_kernel_range(const uintptr_t pgd, uintptr_t begin, const uintptr_t end,
                             const uint64_t flags) {
  while (begin < end) {
    page_map_kernel_into(pgd, phys_to_virt_page(begin), flags);
    begin += PAGE_SIZE;
  }
}

void page_init_tables(void) {
  const uintptr_t pgd = page_alloc(/* order = */ 0, PF_KERNEL);

  memory_zero(phys_to_virt_array(pgd), PAGE_SIZE);

  // TODO(dstechenko): map code/data separately with rules
  map_kernel_range(pgd, PHYSICAL_MEMORY_START, PHYSICAL_DEVICE_MEMORY_START, MMU_KERNEL_PAGES_FLAGS);
  map_kernel_range(pgd, PHYSICAL_DEVICE_MEMORY_START, PHYSICAL_DEVICE_MEMORY_END, MMU_DEVICE_PAGES_FLAGS);
  map_kernel_range(pgd, PHYSICAL_DEVICE_MEMORY_END, PHYSICAL_MEMORY_END, MMU_KERNEL_PAGES_FLAGS);

  // TODO(dstechenko): want to unset user here, but we need to init cpus
  cpu_set_kernel_pt(pgd);
}

void page_map_user(struct task *task, struct page page) {
  bool created;
  struct task_memory *memory;
  uintptr_t pgd, pud, pmd, pte;

  ASSERT(task);
  memory = &task->memory;
  ASSERT(memory->context);

  if (!memory->context->pgd) {
    memory->context->pgd = page_alloc(/* order = */ 0, PF_KERNEL);
    memory_zero(phys_to_virt_array(memory->context->pgd), PAGE_SIZE);
    memory->kernel_pages[memory->kernel_pages_count++] = phys_to_virt_page(memory->context->pgd);
  }
  pgd = memory->context->pgd;

  pud = map_table(phys_to_virt_array(pgd), PGD_SHIFT, page.vaddr, &created);
  if (created) {
    memory->kernel_pages[memory->kernel_pages_count++] = phys_to_virt_page(pud);
  }

  pmd = map_table(phys_to_virt_array(pud), PUD_SHIFT, page.vaddr, &created);
  if (created) {
    memory->kernel_pages[memory->kernel_pages_count++] = phys_to_virt_page(pmd);
  }

  pte = map_table(phys_to_virt_array(pmd), PMD_SHIFT, page.vaddr, &created);
  if (created) {
    memory->kernel_pages[memory->kernel_pages_count++] = phys_to_virt_page(pte);
  }

  // TODO(dstechenko): map code/data separately with rules
  map_table_entry(phys_to_virt_array(pte), page, MMU_USER_FLAGS);
  memory->user_pages[memory->user_pages_count++] = page;
}

uintptr_t phys_to_virt(const uintptr_t paddr) { return paddr + VIRTUAL_MEMORY_OFFSET; }

uintptr_t virt_to_phys(const uintptr_t vaddr) { return vaddr - VIRTUAL_MEMORY_OFFSET; }
