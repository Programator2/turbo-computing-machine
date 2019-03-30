#ifndef TODO_LIST_H
#define TODO_LIST_H

#include "todo.h"

void insert_after(struct todo_item* old, struct todo_item* new);
void insert_before(struct todo_item* old, struct todo_item* new);
  
#endif /* TODO_LIST_H */
