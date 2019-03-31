#include <stdbool.h>
#include <stdio.h>

#include "file.h"
#include "todo.h"

void print_todos(struct todo_item* head)
{
  struct todo_item* iter_todo = head;
  char* buffer = NULL;
  int counter = 1;
  
  while (iter_todo) {
    buffer = todo_item_to_str(iter_todo);
    printf("%2d) ", counter++);
    puts(buffer);
    do {
      iter_todo = iter_todo->next;
    } while (iter_todo && iter_todo->done);
  }
}

int add_todo_item(struct todo_item* head)
{
  char* buffer;
  struct todo_item* todo;
  int ret;
  
  printf("Type new todo item and press ENTER\n");
  buffer = read_line(stdin);
  if (!buffer)
    return -1;
  todo = new_todo_item();
  if (!todo)
    return -1;
  ret = parse_todo_item(buffer, todo);
  if (ret) {
    free_todo_item(todo);
    return ret;
  }
  insert_todo_item(head, todo);
  return 0;
}

int set_item_id_done(struct todo_item* head, int todo_id)
{
  int counter = 1;
  struct todo_item* iter;

  iter = head;

  while (iter->done) {
    if (!iter->next) {
      return -1;
    }
    iter = iter->next;
  }
  
  while (counter != todo_id) {
    if (!iter->next) {
      return -1;
    }
    iter = iter->next;
    counter++;
  }

  iter->done = true;
  return 0;
}

int get_and_dispatch_input(struct todo_item* head)
{
  #define INPUT_SIZE 16

  int ret;
  int todo_id;
  char operation;
  
  char input[INPUT_SIZE];
  fgets(input, INPUT_SIZE, stdin);

  if (input[0] == 'h') {
    printf("h - show this help\n"
	   "NUM t - check todo item NUM as done\n"
           "a - add new todo item\n"
	   "q - save todo items and quit\n"
	   "\n"
	   "todo items have following format:\n"
	   "(A) 2019-03-27 write track for the +StarWarsMovie @music due:2019-05-10\n"
	   " ^  ^                              ^              ^      ^-key/value tag\n"
	   " |  |                              |              |-context tag\n"
	   " |  |                              |-project tag\n"
	   " |  |-creation date (optional)\n"
	   " -priority (optional)\n\n");
    return 0;
  }

  if (input[0] == 'q')
    return 1;

  if (input[0] == 'a') {
    ret = add_todo_item(head);
    if (ret)
      printf("Error while adding todo item\n");
    return 0;
  }

  ret = sscanf(input, "%d %1c\n", &todo_id, &operation);
  if (ret != 2 || operation != 't') {
    printf("Invalid input\n");
    return 0;
  }
  ret = set_item_id_done(head, todo_id);
  if (ret)
    printf("Invalid todo id\n");
  return 0;
}
