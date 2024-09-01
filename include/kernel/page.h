// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_PAGE_H
#define KERNEL_PAGE_H

#include <asm/page-defs.h>
#include <asm/atomic.h>

#include <kernel/list.h>
#include <kernel/types.h>

#define PF_KERNEL BIT(0)
#define PF_ATOMIC BIT(1)
ALIAS(pageflags_t, uint64_t);

struct task;

struct page {
  uintptr_t vaddr;
  uintptr_t paddr;
};

void page_init(void);
void page_init_sections(void);
void page_init_tables(void);
void page_debug(size_t limit);

uintptr_t page_alloc(size_t order, pageflags_t flags);
void page_free(uintptr_t page);
void page_reserve_range(uintptr_t begin, uintptr_t end);

uintptr_t page_get_kernel(size_t order);
uintptr_t page_get_user(struct task *task, uintptr_t vaddr, size_t order);
void page_map_user(struct task *task, struct page page);
void page_map_kernel(struct page page);
int page_copy_user(const struct task *src, struct task *dst);
void page_cache_clear(uintptr_t page);

uintptr_t phys_to_virt(uintptr_t paddr);
uintptr_t virt_to_phys(uintptr_t vaddr);

/////////////////////////////////////////////////////////////////////////////////////

/* ALIAS(pagestate_t, uint64_t); */

/* struct page { */
/*   pagestate_t state; */
/*   atomic32_t refs; */
/*   struct list_head free; */
/* }; */

/* void page_init_alloc(void); */
/* struct page page_alloc(size_t order, pageflags_t flags); */
/* void page_free(struct page *page); */

/* uintptr_t page_to_phys(struct page *page); */
/* struct page *phys_to_page(uintptr_t page); */

#endif // !KERNEL_PAGE_H
