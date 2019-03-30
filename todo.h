#ifndef TODO_TODO_H
#define TODO_TODO_H

#include <stdbool.h>
#include <time.h>

struct todo_item {
  struct todo_item* prev;
  struct todo_item* next;

  bool done;
  char priority;
  struct tm completion_tm;
  struct tm creation_tm;
  char* description;
};

struct todo_item* new_todo_item(void);
void free_todo_item(struct todo_item* todo);
struct todo_item* load_todo_items(void);
char* todo_item_to_str(struct todo_item* todo);
int parse_todo_item(char* buffer, struct todo_item* todo);
int save_todo_items(struct todo_item* head);
void insert_todo_item(struct todo_item* head, struct todo_item* new);

#endif /* TODO_TODO_H */
