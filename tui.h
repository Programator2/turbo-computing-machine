#ifndef TODO_TUI_H
#define TODO_TUI_H

#include "todo.h"

void print_todos(struct todo_item* head);
int get_and_dispatch_input(struct todo_item* head);

#endif /* TODO_TUI_H */
