// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_ASSERT_H
#define KERNEL_ASSERT_H

#include <kernel/config.h>
#include <kernel/types.h>

#if CONFIG_ENABLED(CONFIG_DEBUG)
#define ABORT() abort_handle(__FILE__, __LINE__)
#define ASSERT(cond) assert_handle(cond, #cond, __FILE__, __LINE__)
#else // !CONFIG_ENABLED(CONFIG_DEBUG)
#define ABORT() do {} while (false)
#define ASSERT(cond) do {} while (false)
#endif // CONFIG_ENABLED(CONFIG_DEBUG)

#define STATIC_ASSERT(cond, name) typedef char static_assert_##name[(cond) ? 1 : -1]

void abort_handle(const char *file, int line);
void assert_handle(bool cond, const char *ctx, const char *file, int line);

#endif // !KERNEL_ASSERT_H
