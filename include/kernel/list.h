// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_LIST_H
#define KERNEL_LIST_H

#include <kernel/ptrs.h>
#include <kernel/types.h>

struct list_head {
  struct list_head *prev;
  struct list_head *next;
};

void list_head_init(struct list_head *list);
bool list_empty(const struct list_head *list);
void list_add_tail(struct list_head *list, struct list_head *node);
void list_add_head(struct list_head *list, struct list_head *node);
void list_del(struct list_head *node);
size_t list_len(struct list_head *list);
struct list_head *list_head(struct list_head *list);
struct list_head *list_tail(struct list_head *list);
bool list_is_head(struct list_head *list, struct list_head *node);
bool list_is_tail(struct list_head *list, struct list_head *node);

#define LIST_HEAD_INIT(name) \
  struct list_head name = {.prev = &name, .next = &name}

#define LIST_FOR_EACH(list, elem) \
  for (struct list_head *elem = list->next; elem != list; elem = elem->next)

#define LIST_FOR_EACH_PREV(list, elem) \
  for (struct list_head *elem = list->prev; elem != list; elem = elem->prev)

#define LIST_ENTRY(node, type, member) \
  (container_of(node, type, member))

#define LIST_HEAD_ENTRY(list, type, member) \
  (LIST_ENTRY(list_head(list), type, member))

#define LIST_TAIL_ENTRY(list, type, member) \
  (LIST_ENTRY(list_tail(list), type, member))

#define LIST_FOR_EACH_ENTRY(list, entry, member) \
  for (struct list_head *elem = list->next; elem != list; elem = elem->next) \
    if ((entry = LIST_ENTRY(elem, typeof(*entry), member)))

#endif // !KERNEL_LIST_H
