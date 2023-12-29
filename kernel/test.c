// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/abort.h>
#include <asm/atomic.h>

#include <kernel/test.h>
#include <kernel/types.h>

#include <drivers/random.h>

#define TEST_ASSERT(cond)                                                                          \
  {                                                                                                \
    if (!(cond)) {                                                                                 \
      abort();                                                                                     \
    }                                                                                              \
  }

static void test_drivers_random(void) {
  uint32_t out;
  size_t iter = 0;
  static const size_t max_iter = 100000;

  while (iter++ < max_iter) {
    out = random_get(1, 10);
    TEST_ASSERT(out >= 1 && out <= 10);
  }
}

static void test_kernel_atomic32(void) {
  int32_t tmp;
  atomic32_t obj = ATOMIC_INIT(1);

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

static void test_kernel_print(void) {}

static void test_kernel_log(void) {}

void test_all(void) {
  test_drivers();
  test_kernel();
  test_user();
}

void test_drivers(void) { test_drivers_random(); }

void test_kernel(void) {
  test_kernel_atomic32();
  test_kernel_atomic64();
  test_kernel_print();
  test_kernel_log();
}

void test_user(void) {}
