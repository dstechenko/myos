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

#define LIST_HEAD_INIT(name) \
  struct list_head name = {.prev = &name, .next = &name}

void list_head_init(struct list_head *list);
bool list_empty(const struct list_head *list);
void list_add_tail(struct list_head *list, struct list_head *node);
void list_add_head(struct list_head *list, struct list_head *node);
void list_del(struct list_head *node);
size_t list_len(struct list_head *list);
struct list_head *list_head(struct list_head *list);
struct list_head *list_tail(struct list_head *list);

#define LIST_FOR_EACH(list, name) \
  for (struct list_head *name = list->next; name != list; name = name->next)

#endif // !KERNEL_LIST_H
