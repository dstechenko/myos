// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_UTIL_ASSERT_H
#define KERNEL_UTIL_ASSERT_H

#include <kernel/config.h>

#if CONFIG_ENABLED(CONFIG_DEBUG)
#define ABORT() handle_abort()
#define ASSERT(cond) handle_assert(cond, #cond)
#else // !CONFIG_ENABLED(CONFIG_DEBUG)
#define ABORT()                                                                \
  do {                                                                         \
  } while (false)
#define ASSERT(cond)                                                           \
  do {                                                                         \
  } while (false)
#endif // CONFIG_ENABLED(CONFIG_DEBUG)

void handle_abort(void);
void handle_assert(bool cond, const char *ctx);

#endif // !KERNEL_UTIL_ASSERT_H
