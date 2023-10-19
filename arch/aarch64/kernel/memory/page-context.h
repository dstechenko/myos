// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef ARCH_AARCH64_KERNEL_MEMORY_PAGE_CONTEXT_H
#define ARCH_AARCH64_KERNEL_MEMORY_PAGE_CONTEXT_H

struct page_context {
  uintptr_t pgd;
};

#endif // !ARCH_AARCH64_KERNEL_MEMORY_PAGE_CONTEXT_H
