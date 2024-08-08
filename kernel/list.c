// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/assert.h>
#include <kernel/list.h>

void list_head_init(struct list_head *list) {
  ASSERT(list);
  list->prev = list;
  list->next = list;
}

bool list_empty(const struct list_head *list) {
  ASSERT(list);
  return list->next == list;
}

void list_add_tail(struct list_head *list, struct list_head *node) {
  struct list_head *prev;
  ASSERT(list);
  ASSERT(node);
  prev = list->prev;
  node->next = list;
  node->prev = prev;
  prev->next = node;
  list->prev = node;
}

void list_add_head(struct list_head *list, struct list_head *node) {
  struct list_head *next;
  ASSERT(list);
  ASSERT(node);
  next = list->next;
  node->next = next;
  node->prev = list;
  next->prev = node;
  list->next = node;
}

void list_del(struct list_head *node) {
  struct list_head *prev, *next;
  ASSERT(node);
  prev = node->prev;
  next = node->next;
  prev->next = next;
  next->prev = prev;
}

size_t list_len(struct list_head *list) {
  ASSERT(list);
  size_t len = 0;
  LIST_FOR_EACH(list, node) { len++; }
  return len;
}

struct list_head *list_head(struct list_head *list) {
  ASSERT(list);
  ASSERT(!list_empty(list));
  return list->next;
}

struct list_head *list_tail(struct list_head *list) {
  ASSERT(list);
  ASSERT(!list_empty(list));
  return list->prev;
}
