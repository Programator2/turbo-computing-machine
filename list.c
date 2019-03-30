#include "todo.h"

void insert_after(struct todo_item* old, struct todo_item* new)
{
  struct todo_item* storage;
  
  if (!old->next) {
    old->next = new;
    new->prev = old;
  } else {
    storage = old->next;
    old->next = new;
    new->prev = old;

    storage->prev = new;
    new->next = storage;
  }
}

void insert_before(struct todo_item* old, struct todo_item* new)
{
  struct todo_item* storage;
  
  if (!old->prev) {
    old->prev = new;
    new->next = old;
  } else {
    storage = old->prev;
    old->prev = new;
    new->next = old;

    storage->next = new;
    new->prev = storage;
  }
}
