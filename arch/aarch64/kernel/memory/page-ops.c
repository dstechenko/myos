// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "page-ops.h"

#include <stddef.h>

#include <asm/memory-defs.h>
#include <asm/mmu-defs.h>
#include <asm/page-defs.h>
#include <asm/sections.h>

#include <kernel/logging/log.h>
#include <kernel/util/assert.h>
#include <kernel/util/bits.h>

#include "page-context.h"

/**
 *                                  Descriptor format
 * +------------------------------------------------------------------------------------------+
 * | Upper attributes | Address (bits 47:12) | Lower attributes | Block/table bit | Valid bit |
 * +------------------------------------------------------------------------------------------+
 * 63                 47                     11                 2                 1           0
 *
 */

#define GET_DESC_VALID_BIT(desc) (desc & BIT(0))
#define GET_DESC_TABLE_BIT(desc) (desc & BIT(1))
#define GET_DESC_ADDR_BITS(desc) (desc & (BIT(48) - 1) & ~(BIT(12) - 1))
#define GET_DESC_LOW_ATTR_BITS(desc) (desc & (BIT(12) - 1) & ~(BIT(2) - 1))

static void log_page_entries(const uintptr_t table) {
  uintptr_t *cursor = (uintptr_t *)table;
  size_t empty = 0;

  ASSERT(cursor);

  for (size_t i = 0; i < PAGES_PER_TABLE; i++) {
    if (!cursor[i]) {
      empty++;
      continue;
    }

    if (empty) {
      LOG_DEBUG("... %u empty entries ...", empty);
      empty = 0;
    }

    const bool is_valid = GET_DESC_VALID_BIT(cursor[i]);
    const bool is_table = GET_DESC_TABLE_BIT(cursor[i]);
    const uintptr_t addr = GET_DESC_ADDR_BITS(cursor[i]);
    const uint64_t flags = GET_DESC_LOW_ATTR_BITS(cursor[i]);

    LOG_DEBUG("> %s [%s]", is_table ? "table" : "block", is_valid ? "valid" : "invalid");
    LOG_DEBUG("  bits: %lx", cursor[i]);
    LOG_DEBUG("  addr: %lx", addr);
    LOG_DEBUG(" flags: %lx", flags);
  }
  if (empty)
    LOG_DEBUG("... %u empty entries ...", empty);
}

void log_page_global_directory(const uintptr_t pgd) {
  uintptr_t *pud, *pmd, *pte;

  ASSERT(pgd);
  pud = (uintptr_t *)pgd;

  LOG_DEBUG("Page Global Directory (physical address %lx)", pgd);
  log_page_entries(pgd);

  for (size_t i = 0; i < PAGES_PER_TABLE; i++)
    if (pud[i]) {
      LOG_DEBUG("Page Upper Directory (physical address %lx)", GET_DESC_ADDR_BITS(pud[i]));
      log_page_entries(GET_DESC_ADDR_BITS(pud[i]));
    }

  for (size_t i = 0; i < PAGES_PER_TABLE; i++)
    if (pud[i]) {
      pmd = (uintptr_t *)GET_DESC_ADDR_BITS(pud[i]);
      for (size_t j = 0; j < PAGES_PER_TABLE; j++)
        if (pmd[j]) {
          LOG_DEBUG("Page Middle Directory (physical address %lx)", GET_DESC_ADDR_BITS(pmd[j]));
          log_page_entries(GET_DESC_ADDR_BITS(pmd[j]));
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
              LOG_DEBUG("\nPage Table Entry (physical address %lx)", GET_DESC_ADDR_BITS(pte[k]));
              log_page_entries(GET_DESC_ADDR_BITS(pte[k]));
            }
        }
    }
}

/* SECTION_LABEL(section_pgd_boot_start); */
/* SECTION_LABEL(section_pgd_kernel_start); */

void debug_pages(void) {
  /* LOG_DEBUG(""); */
  /* LOG_DEBUG("Boot level"); */
  /* log_page_global_directory(SECTION_ADDR(section_pgd_boot_start)); */
  /* LOG_DEBUG(""); */
  /* LOG_DEBUG("Kernel level"); */
  /* log_page_global_directory(SECTION_ADDR(section_pgd_kernel_start)); */
  /* LOG_DEBUG(""); */
}

// TODO: this is ugly, need to fix...
#define TO_VADDR(addr) (addr + VIRTUAL_MEMORY_START)
#define TO_VADDR_PTR(addr) ((uintptr_t *)TO_VADDR(addr))
#define TO_VADDR_PAGE(addr) ((struct page){.paddr = addr, .vaddr = TO_VADDR(addr)})

void map_user_page(struct task *task, struct page page) {
  bool created;
  struct task_memory *memory;
  uintptr_t pgd, pud, pmd, pte;

  ASSERT(task);
  memory = &task->memory;
  ASSERT(memory->context);

  if (!memory->context->pgd) {
    memory->context->pgd = get_page();
    memory->kernel_pages[memory->kernel_pages_count++] = TO_VADDR_PAGE(memory->context->pgd);
  }
  pgd = memory->context->pgd;

  pud = map_user_table(TO_VADDR_PTR(pgd), PGD_SHIFT, page.vaddr, &created);
  if (created)
    memory->kernel_pages[memory->kernel_pages_count++] = TO_VADDR_PAGE(pud);

  pmd = map_user_table(TO_VADDR_PTR(pud), PUD_SHIFT, page.vaddr, &created);
  if (created)
    memory->kernel_pages[memory->kernel_pages_count++] = TO_VADDR_PAGE(pmd);

  pte = map_user_table(TO_VADDR_PTR(pmd), PMD_SHIFT, page.vaddr, &created);
  if (created)
    memory->kernel_pages[memory->kernel_pages_count++] = TO_VADDR_PAGE(pte);

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
    table[index] = next_table | MMU_TYPE_PAGE_TABLE;
    ret = next_table;
  }

  return ret;
}

void map_user_table_entry(uintptr_t *entry, struct page page) {
  size_t index;

  ASSERT(entry);

  index = get_table_index(PAGE_SHIFT, page.vaddr);
  entry[index] = (page.paddr | MMU_USER_FLAGS);
}
