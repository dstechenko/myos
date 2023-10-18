// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include "page-ops.h"

#include <stddef.h>

#include <kernel/logging/print.h>
#include <kernel/memory/page.h>
#include <kernel/util/assert.h>
#include <kernel/util/bits.h>

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

static void print_page_entries(const uintptr_t table) {
  uintptr_t *cursor = (uintptr_t *)table;
  size_t empty = 0;

  ASSERT(cursor);

  for (size_t i = 0; i < PAGES_PER_TABLE; i++) {
    if (!cursor[i]) {
      empty++;
      continue;
    }

    if (empty) {
      print("... %u empty entries ...\n", empty);
      empty = 0;
    }

    const bool is_valid = GET_DESC_VALID_BIT(cursor[i]);
    const bool is_table = GET_DESC_TABLE_BIT(cursor[i]);
    const uintptr_t addr = GET_DESC_ADDR_BITS(cursor[i]);
    const uint64_t flags = GET_DESC_LOW_ATTR_BITS(cursor[i]);

    print("> %s [%s]\n", is_table ? "table" : "block", is_valid ? "valid" : "invalid");
    print("  bits: %lx\n", cursor[i]);
    print("  addr: %lx\n", addr);
    print(" flags: %lx\n", flags);
  }
  if (empty)
    print("... %u empty entries ... \n", empty);
}

void print_page_global_directory(const uintptr_t pgd) {
  uintptr_t *pud, *pmd, *pte;

  ASSERT(pgd);
  pud = (uintptr_t *)pgd;

  print("\nPage Global Directory (physical address %lx)\n", pgd);
  print_page_entries(pgd);

  for (size_t i = 0; i < PAGES_PER_TABLE; i++)
    if (pud[i]) {
      print("\nPage Upper Directory (physical address %lx)\n", GET_DESC_ADDR_BITS(pud[i]));
      print_page_entries(GET_DESC_ADDR_BITS(pud[i]));
    }

  for (size_t i = 0; i < PAGES_PER_TABLE; i++)
    if (pud[i]) {
      pmd = (uintptr_t *)GET_DESC_ADDR_BITS(pud[i]);
      for (size_t j = 0; j < PAGES_PER_TABLE; j++)
        if (pmd[j]) {
          print("\nPage Middle Directory (physical address %lx)\n", GET_DESC_ADDR_BITS(pmd[j]));
          print_page_entries(GET_DESC_ADDR_BITS(pmd[j]));
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
              print("\nPage Table Entry (physical address %lx)\n", GET_DESC_ADDR_BITS(pte[k]));
              print_page_entries(GET_DESC_ADDR_BITS(pte[k]));
            }
        }
    }
}

void section_pgd_boot_start(void);
void section_pgd_kernel_start(void);

void debug_pages(void) {
  print("\nBoot level\n");
  print_page_global_directory((uintptr_t)section_pgd_boot_start);

  /* print("\nKernel level\n"); */
  /* print_page_global_directory((uintptr_t)section_pgd_kernel_start); */
}
