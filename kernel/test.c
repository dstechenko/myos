// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/atomic.h>
#include <asm/sections.h>

#include <kernel/assert.h>
#include <kernel/config.h>
#include <kernel/list.h>
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
  TEST_ASSERT(&outer == container_of(&outer.inner, struct outer, inner));
}

static void test_kernel_list(void) {
  struct list_head *contents[4] = {};
  struct list_head list, elem1, elem2, elem3, elem4;
  struct list_head *list_ptr = &list;
  size_t index;

  list_head_init(&list);
  TEST_ASSERT(list_empty(&list));
  TEST_ASSERT(list_len(&list) == 0);

  list_add_tail(&list, &elem1);
  TEST_ASSERT(!list_empty(&list));
  TEST_ASSERT(list_len(&list) == 1);

  list_add_tail(&list, &elem2);
  TEST_ASSERT(!list_empty(&list));
  TEST_ASSERT(list_len(&list) == 2);

  list_add_tail(&list, &elem3);
  TEST_ASSERT(!list_empty(&list));
  TEST_ASSERT(list_len(&list) == 3);

  list_add_tail(&list, &elem4);
  TEST_ASSERT(!list_empty(&list));
  TEST_ASSERT(list_len(&list) == 4);

  list_del(&elem1);
  TEST_ASSERT(!list_empty(&list));
  TEST_ASSERT(list_len(&list) == 3);

  list_del(&elem1);
  TEST_ASSERT(!list_empty(&list));
  TEST_ASSERT(list_len(&list) == 3);

  list_del(&elem2);
  TEST_ASSERT(!list_empty(&list));
  TEST_ASSERT(list_len(&list) == 2);

  list_del(&elem3);
  TEST_ASSERT(!list_empty(&list));
  TEST_ASSERT(list_len(&list) == 1);

  list_del(&elem4);
  TEST_ASSERT(list_empty(&list));
  TEST_ASSERT(list_len(&list) == 0);

  list_add_head(&list, &elem1);
  list_add_head(&list, &elem2);
  list_add_head(&list, &elem3);
  list_add_head(&list, &elem4);
  TEST_ASSERT(!list_empty(&list));
  TEST_ASSERT(list_len(&list) == 4);
  index = 0;
  LIST_FOR_EACH(list_ptr, elem) { contents[index++] = elem; }
  TEST_ASSERT(contents[0] == &elem4);
  TEST_ASSERT(contents[1] == &elem3);
  TEST_ASSERT(contents[2] == &elem2);
  TEST_ASSERT(contents[3] == &elem1);
  TEST_ASSERT(list_head(&list) == &elem4);
  TEST_ASSERT(list_tail(&list) == &elem1);
  list_del(&elem1);
  list_del(&elem2);
  list_del(&elem3);
  list_del(&elem4);
  TEST_ASSERT(list_empty(&list));
  TEST_ASSERT(list_len(&list) == 0);

  list_add_tail(&list, &elem1);
  list_add_tail(&list, &elem2);
  list_add_tail(&list, &elem3);
  list_add_tail(&list, &elem4);
  TEST_ASSERT(!list_empty(&list));
  TEST_ASSERT(list_len(&list) == 4);
  index = 0;
  LIST_FOR_EACH(list_ptr, elem) { contents[index++] = elem; }
  TEST_ASSERT(contents[0] == &elem1);
  TEST_ASSERT(contents[1] == &elem2);
  TEST_ASSERT(contents[2] == &elem3);
  TEST_ASSERT(contents[3] == &elem4);
  TEST_ASSERT(list_head(&list) == &elem1);
  TEST_ASSERT(list_tail(&list) == &elem4);
  list_del(&elem1);
  list_del(&elem2);
  list_del(&elem3);
  list_del(&elem4);
  TEST_ASSERT(list_empty(&list));
  TEST_ASSERT(list_len(&list) == 0);
}

struct entry {
  struct list_head node;
};

static void test_kernel_entry_list(void) {
  struct entry *contents[4] = {};
  struct entry entry1, entry2, entry3, entry4;
  struct entry *entry;
  struct list_head list;
  struct list_head *list_ptr = &list;
  size_t index;

  list_head_init(&list);
  TEST_ASSERT(list_empty(&list));
  TEST_ASSERT(list_len(&list) == 0);

  list_add_tail(&list, &entry1.node);
  TEST_ASSERT(!list_empty(&list));
  TEST_ASSERT(list_len(&list) == 1);

  list_add_tail(&list, &entry2.node);
  TEST_ASSERT(!list_empty(&list));
  TEST_ASSERT(list_len(&list) == 2);

  list_add_tail(&list, &entry3.node);
  TEST_ASSERT(!list_empty(&list));
  TEST_ASSERT(list_len(&list) == 3);

  list_add_tail(&list, &entry4.node);
  TEST_ASSERT(!list_empty(&list));
  TEST_ASSERT(list_len(&list) == 4);

  list_del(&entry1.node);
  TEST_ASSERT(!list_empty(&list));
  TEST_ASSERT(list_len(&list) == 3);

  list_del(&entry1.node);
  TEST_ASSERT(!list_empty(&list));
  TEST_ASSERT(list_len(&list) == 3);

  list_del(&entry2.node);
  TEST_ASSERT(!list_empty(&list));
  TEST_ASSERT(list_len(&list) == 2);

  list_del(&entry3.node);
  TEST_ASSERT(!list_empty(&list));
  TEST_ASSERT(list_len(&list) == 1);

  list_del(&entry4.node);
  TEST_ASSERT(list_empty(&list));
  TEST_ASSERT(list_len(&list) == 0);

  list_add_head(&list, &entry1.node);
  list_add_head(&list, &entry2.node);
  list_add_head(&list, &entry3.node);
  list_add_head(&list, &entry4.node);
  TEST_ASSERT(!list_empty(&list));
  TEST_ASSERT(list_len(&list) == 4);
  index = 0;
  LIST_FOR_EACH_ENTRY(list_ptr, entry, node) { contents[index++] = entry; }
  TEST_ASSERT(contents[0] == &entry4);
  TEST_ASSERT(contents[1] == &entry3);
  TEST_ASSERT(contents[2] == &entry2);
  TEST_ASSERT(contents[3] == &entry1);
  TEST_ASSERT(LIST_HEAD_ENTRY(&list, struct entry, node) == &entry4);
  TEST_ASSERT(LIST_TAIL_ENTRY(&list, struct entry, node) == &entry1);
  list_del(&entry1.node);
  list_del(&entry2.node);
  list_del(&entry3.node);
  list_del(&entry4.node);
  TEST_ASSERT(list_empty(&list));
  TEST_ASSERT(list_len(&list) == 0);

  list_add_tail(&list, &entry1.node);
  list_add_tail(&list, &entry2.node);
  list_add_tail(&list, &entry3.node);
  list_add_tail(&list, &entry4.node);
  TEST_ASSERT(!list_empty(&list));
  TEST_ASSERT(list_len(&list) == 4);
  index = 0;
  LIST_FOR_EACH_ENTRY(list_ptr, entry, node) { contents[index++] = entry; }
  TEST_ASSERT(contents[0] == &entry1);
  TEST_ASSERT(contents[1] == &entry2);
  TEST_ASSERT(contents[2] == &entry3);
  TEST_ASSERT(contents[3] == &entry4);
  TEST_ASSERT(LIST_HEAD_ENTRY(&list, struct entry, node) == &entry1);
  TEST_ASSERT(LIST_TAIL_ENTRY(&list, struct entry, node) == &entry4);
  list_del(&entry1.node);
  list_del(&entry2.node);
  list_del(&entry3.node);
  list_del(&entry4.node);
  TEST_ASSERT(list_empty(&list));
  TEST_ASSERT(list_len(&list) == 0);
}

static void test_drivers(void) {}

static void test_kernel(void) {
  test_kernel_atomic32();
  test_kernel_atomic64();
  test_kernel_container_of();
  test_kernel_list();
  test_kernel_entry_list();
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
