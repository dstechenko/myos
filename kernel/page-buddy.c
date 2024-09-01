// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/memory-defs.h>
#include <asm/page-defs.h>

#include <kernel/assert.h>
#include <kernel/bits.h>
#include <kernel/config.h>
#include <kernel/list.h>
#include <kernel/page.h>
#include <kernel/spinlock.h>
#include <kernel/types.h>

/* #define PAGE_LEVELS 20 */

/* static SPIN_LOCK_INIT(page_free_lock); */
/* static list_head page_free_list[PAGE_LEVELS]; */
/* static struct page page_memory_map[1]; */

/* #define PAGE_FREE_MASK BIT(8) */
/* #define PAGE_LEVEL_MASK (BIT(8) - 1) */

/* static void page_set_level(struct page *page, size_t level) { */
/*   ASSERT(page); */
/*   ASSERT(!(level & ~PAGE_LEVEL_MASK)); */
/*   page->state = level | (page->state & ~PAGE_LEVEL_MASK); */
/* } */

/* static size_t page_get_level(struct page *page) { ASSERT(page); } */

/* static void page_set_free(struct page *page) { */
/*   ASSERT(page); */
/*   page->state &= ~PAGE_FREE_MASK; */
/* } */

/* static void page_set_busy(struct page *page) { */
/*   ASSERT(page); */
/*   page->state |= PAGE_FREE_MASK; */
/* } */

/* static bool page_is_free(struct page *page) { */
/*   ASSERT(page); */
/*   return !!PAGE_FREE_MASK(page); */
/* } */

/* void page_init_alloc(void) { */
/*   for (size_t idx = 0; idx < PAGE_LEVELS; idx++) { */
/*     list_head_init(&page_free_list[idx]); */
/*   } */
/* } */

/* struct page page_alloc(size_t order, pageflags_t flags) {} */

/* void page_free(struct page *page) { ASSERT(page); } */

/* uintptr_t page_to_phys(struct page *page) {} */

/* struct page *phys_to_page(uintptr_t page) {} */
