// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_UTIL_ASSERT_H
#define KERNEL_UTIL_ASSERT_H

#include <kernel/config.h>

#if CONFIG_ENABLED(CONFIG_DEBUG)
#define ABORT() handle_abort(__FILE__, __LINE__)
#define ASSERT(cond) handle_assert(cond, #cond, __FILE__, __LINE__)
#else // !CONFIG_ENABLED(CONFIG_DEBUG)
#define ABORT()                                                                \
  do {                                                                         \
  } while (false)
#define ASSERT(cond)                                                           \
  do {                                                                         \
  } while (false)
#endif // CONFIG_ENABLED(CONFIG_DEBUG)

void handle_abort(const char *file, int line);
void handle_assert(bool cond, const char *ctx, const char *file, int line);

#endif // !KERNEL_UTIL_ASSERT_H
