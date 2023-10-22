// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "page-ops.h"

#include <stddef.h>

#include <asm/memory-defs.h>
#include <asm/mmu-defs.h>
#include <asm/page-defs.h>
#include <asm/registers.h>

#include <kernel/logging/log.h>
#include <kernel/memory/ops.h>
#include <kernel/util/assert.h>
#include <kernel/util/bits.h>
#include <kernel/util/ptrs.h>

#include "page-context.h"

#define GET_DESC_VALID_BIT(desc) (desc & BIT(0))
#define GET_DESC_TABLE_BIT(desc) (desc & BIT(1))
#define GET_DESC_ADDR_BITS(desc) (desc & (BIT(48) - 1) & ~(BIT(12) - 1))
#define GET_DESC_LOW_ATTR_BITS(desc) (desc & (BIT(12) - 1) & ~(BIT(2) - 1))

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
  uintptr_t *pud = (uintptr_t *)pgd, *pmd, *pte;

  LOG_DEBUG("  Page Global Directory (physical address %lx)", pgd);
  if (!pgd)
    return;
  log_page_entries(pgd, limit);

  for (size_t i = 0; i < PAGES_PER_TABLE; i++)
    if (pud[i]) {
      LOG_DEBUG("  Page Upper Directory (physical address %lx)", GET_DESC_ADDR_BITS(pud[i]));
      log_page_entries(GET_DESC_ADDR_BITS(pud[i]), limit);
    }

  for (size_t i = 0; i < PAGES_PER_TABLE; i++)
    if (pud[i]) {
      pmd = (uintptr_t *)GET_DESC_ADDR_BITS(pud[i]);
      for (size_t j = 0; j < PAGES_PER_TABLE; j++)
        if (pmd[j]) {
          LOG_DEBUG("  Page Middle Directory (physical address %lx)", GET_DESC_ADDR_BITS(pmd[j]));
          log_page_entries(GET_DESC_ADDR_BITS(pmd[j]), limit);
        }
    }

  for (size_t i = 0; i < PAGES_PER_TABLE; i++)
    if (pud[i]) {
      pmd = (uintptr_t *)GET_DESC_ADDR_BITS(pud[i]);
      for (size_t j = 0; j < PAGES_PER_TABLE; j++)
        if (pmd[j]) {
          pte = (uintptr_t *)GET_DESC_ADDR_BITS(pmd[j]);
          for (size_t k = 0; k < PAGES_PER_TABLE; k++)
            if (pte[k] && GET_DESC_TABLE_BIT(pte[k])) {
              LOG_DEBUG("  Page Table Entry (physical address %lx)", GET_DESC_ADDR_BITS(pte[k]));
              log_page_entries(GET_DESC_ADDR_BITS(pte[k]), limit);
            }
        }
    }
}

// TODO(dstechenko): this is ugly, need to fix (phys_to_virt / virt_to_phys)
#define TO_VADDR(addr) (addr + VIRTUAL_MEMORY_START)
#define TO_VADDR_PTR(addr) ((uintptr_t *)TO_VADDR(addr))
#define TO_VADDR_PAGE(addr) ((struct page){.paddr = addr, .vaddr = TO_VADDR(addr)})

void page_debug(const size_t limit) {
  LOG_DEBUG("Memory configurations:");
  LOG_DEBUG("  Physical memory start        - %lx", PHYSICAL_MEMORY_START);
  LOG_DEBUG("  Physical memory end:         - %lx", PHYSICAL_MEMORY_END);
  LOG_DEBUG("  Physical memory size:        - %lx", PHYSICAL_MEMORY_SIZE);
  LOG_DEBUG("  Physical device memory start - %lx", PHYSICAL_DEVICE_MEMORY_START);
  LOG_DEBUG("  Physical device memory end   - %lx", PHYSICAL_DEVICE_MEMORY_END);
  LOG_DEBUG("  Physical device memory size  - %lx", PHYSICAL_DEVICE_MEMORY_SIZE);
  LOG_DEBUG("  Virtual memory start         - %lx", VIRTUAL_MEMORY_START);
  LOG_DEBUG("  Virtual memory end           - %lx", VIRTUAL_MEMORY_END);
  LOG_DEBUG("  Virtual memory size          - %lx", VIRTUAL_MEMORY_SIZE);
  LOG_DEBUG("  Virtual device memory start  - %lx", VIRTUAL_DEVICE_MEMORY_START);
  LOG_DEBUG("  Virtual device memory end    - %lx", VIRTUAL_DEVICE_MEMORY_END);
  LOG_DEBUG("  Virtual device memory size   - %lx", VIRTUAL_DEVICE_MEMORY_SIZE);
  LOG_DEBUG("  Boot load address            - %lx", BOOT_LOAD_ADDRESS);
  LOG_DEBUG("User pages:");
  log_page_global_directory(registers_get_user_page_table(), limit);
  LOG_DEBUG("Kernel pages:");
  log_page_global_directory(registers_get_kernel_page_table(), limit);
}

void page_init(void) {}

// TODO(dstechenko): fix memzero on pages
void map_user_page(struct task *task, struct page page) {
  bool created;
  struct task_memory *memory;
  uintptr_t pgd, pud, pmd, pte;

  ASSERT(task);
  memory = &task->memory;
  ASSERT(memory->context);

  if (!memory->context->pgd) {
    memory->context->pgd = get_page();
    memzero(TO_VADDR_PTR(memory->context->pgd), PAGE_SIZE - 1);
    memory->kernel_pages[memory->kernel_pages_count++] = TO_VADDR_PAGE(memory->context->pgd);
  }
  pgd = memory->context->pgd;

  pud = map_user_table(TO_VADDR_PTR(pgd), PGD_SHIFT, page.vaddr, &created);
  if (created) {
    memory->kernel_pages[memory->kernel_pages_count++] = TO_VADDR_PAGE(pud);
  }

  pmd = map_user_table(TO_VADDR_PTR(pud), PUD_SHIFT, page.vaddr, &created);
  if (created) {
    memory->kernel_pages[memory->kernel_pages_count++] = TO_VADDR_PAGE(pmd);
  }

  pte = map_user_table(TO_VADDR_PTR(pmd), PMD_SHIFT, page.vaddr, &created);
  if (created) {
    memory->kernel_pages[memory->kernel_pages_count++] = TO_VADDR_PAGE(pte);
  }

  map_user_table_entry(TO_VADDR_PTR(pte), page);
  memory->user_pages[memory->user_pages_count++] = page;
}

static size_t get_table_index(size_t shift, uintptr_t vaddr) { return (vaddr >> shift) & (PAGES_PER_TABLE - 1); }

uintptr_t map_user_table(uintptr_t *table, size_t shift, uintptr_t vaddr, bool *created) {
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
    uintptr_t next_table = get_page();
    memzero(TO_VADDR_PTR(next_table), PAGE_SIZE - 1);
    table[index] = next_table | MMU_TYPE_PAGE_TABLE;
    ret = next_table;
  }

  return ret;
}

void map_user_table_entry(uintptr_t *entry, struct page page) {
  size_t index;

  ASSERT(entry);

  index = get_table_index(PAGE_SHIFT, page.vaddr);
  entry[index] = page.paddr | MMU_USER_FLAGS;
}
