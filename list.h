#ifndef TODO_LIST_H
#define TODO_LIST_H

#include "todo.h"

/**
 * @brief Inserts item to a linked list.
 *
 * Insert item @c new after item @c old.
 */
void insert_after(struct todo_item* old, struct todo_item* new);

/**
 * @brief Inserts item to a linked list.
 *
 * Insert item @c new before item @c old.
 */
void insert_before(struct todo_item* old, struct todo_item* new);
  
#endif /* TODO_LIST_H */
