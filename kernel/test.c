// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/atomic.h>
#include <asm/sections.h>

#include <kernel/assert.h>
#include <kernel/config.h>
#include <kernel/log.h>
#include <kernel/ptrs.h>
#include <kernel/test.h>
#include <kernel/types.h>

#define TEST_ASSERT(cond) ASSERT(cond)

SECTIONS(section_kernel);

static void test_kernel_atomic32(void) {
  int32_t tmp;
  static atomic32_t obj = ATOMIC_INIT(1);

  TEST_ASSERT(atomic32_get(&obj) == 1);

  tmp = atomic32_set(&obj, 2);
  TEST_ASSERT(atomic32_get(&obj) == 2);
  TEST_ASSERT(atomic32_get_relaxed(&obj) == 2);
  TEST_ASSERT(tmp == 1);

  tmp = atomic32_inc(&obj);
  TEST_ASSERT(atomic32_get(&obj) == 3);
  TEST_ASSERT(atomic32_get_relaxed(&obj) == 3);
  TEST_ASSERT(tmp == 2);

  tmp = atomic32_dec(&obj);
  TEST_ASSERT(atomic32_get(&obj) == 2);
  TEST_ASSERT(atomic32_get_relaxed(&obj) == 2);
  TEST_ASSERT(tmp == 3);

  tmp = atomic32_add(&obj, 3);
  TEST_ASSERT(atomic32_get(&obj) == 5);
  TEST_ASSERT(atomic32_get_relaxed(&obj) == 5);
  TEST_ASSERT(tmp == 2);

  tmp = atomic32_sub(&obj, 2);
  TEST_ASSERT(atomic32_get(&obj) == 3);
  TEST_ASSERT(atomic32_get_relaxed(&obj) == 3);
  TEST_ASSERT(tmp == 5);

  tmp = atomic32_cmp_swp(&obj, 3, 5);
  TEST_ASSERT(atomic32_get(&obj) == 5);
  TEST_ASSERT(atomic32_get_relaxed(&obj) == 5);
  TEST_ASSERT(tmp == 3);

  tmp = atomic32_cmp_swp(&obj, 4, 6);
  TEST_ASSERT(atomic32_get(&obj) == 5);
  TEST_ASSERT(atomic32_get_relaxed(&obj) == 5);
  TEST_ASSERT(tmp == 5);
}

static void test_kernel_atomic64(void) {
  int64_t tmp;
  atomic64_t obj = ATOMIC_INIT(1);

  TEST_ASSERT(atomic64_get(&obj) == 1);

  tmp = atomic64_set(&obj, 2);
  TEST_ASSERT(atomic64_get(&obj) == 2);
  TEST_ASSERT(atomic64_get_relaxed(&obj) == 2);
  TEST_ASSERT(tmp == 1);

  tmp = atomic64_inc(&obj);
  TEST_ASSERT(atomic64_get(&obj) == 3);
  TEST_ASSERT(atomic64_get_relaxed(&obj) == 3);
  TEST_ASSERT(tmp == 2);

  tmp = atomic64_dec(&obj);
  TEST_ASSERT(atomic64_get(&obj) == 2);
  TEST_ASSERT(atomic64_get_relaxed(&obj) == 2);
  TEST_ASSERT(tmp == 3);

  tmp = atomic64_add(&obj, 3);
  TEST_ASSERT(atomic64_get(&obj) == 5);
  TEST_ASSERT(atomic64_get_relaxed(&obj) == 5);
  TEST_ASSERT(tmp == 2);

  tmp = atomic64_sub(&obj, 2);
  TEST_ASSERT(atomic64_get(&obj) == 3);
  TEST_ASSERT(atomic64_get_relaxed(&obj) == 3);
  TEST_ASSERT(tmp == 5);

  tmp = atomic64_cmp_swp(&obj, 3, 5);
  TEST_ASSERT(atomic64_get(&obj) == 5);
  TEST_ASSERT(atomic64_get_relaxed(&obj) == 5);
  TEST_ASSERT(tmp == 3);

  tmp = atomic64_cmp_swp(&obj, 4, 6);
  TEST_ASSERT(atomic64_get(&obj) == 5);
  TEST_ASSERT(atomic64_get_relaxed(&obj) == 5);
  TEST_ASSERT(tmp == 5);
}

struct inner {};

struct outer {
  struct inner inner;
};

static void test_kernel_container_of(void) {
  struct outer outer;
  ASSERT(&outer == container_of(&outer.inner, struct outer, inner));
}

static void test_drivers(void) {}

static void test_kernel(void) {
  test_kernel_atomic32();
  test_kernel_atomic64();
  test_kernel_container_of();
}

static void test_user(void) {}

void test_init(void) {
#if CONFIG_ENABLED(CONFIG_KERNEL_TEST_ON_BOOT)
  test_drivers();
  test_kernel();
  test_user();
  LOG_DEBUG("Kernel tests OK");
#endif  // CONFIG_ENABLED(CONFIG_KERNEL_TEST_ON_BOOT)
}
