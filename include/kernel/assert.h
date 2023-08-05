// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_ASSERT_H
#define KERNEL_ASSERT_H

#include <kernel/config.h>

#if CONFIG_ENABLED(CONFIG_DEBUG)
#define ABORT() abort()
#define ASSERT(cond) assert(cond, #cond)
#else // !CONFIG_ENABLED(CONFIG_DEBUG)
#define ABORT()                                                                \
	do {                                                                   \
	} while (false)
#define ASSERT(cond)                                                           \
	do {                                                                   \
	} while (false)
#endif // CONFIG_ENABLED(CONFIG_DEBUG)

void abort();
void assert(bool cond, const char *ctx);

#endif // !KERNEL_ASSERT_H
