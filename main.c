#include <stdio.h>

#include "todo.h"
#include "tui.h"

int main()
{
  // Load todos from file
  struct todo_item* todo_head;
  todo_head = load_todo_items();
  if (!todo_head) {
    puts("todo.txt not available in current directory or has invalid format");
    return -1;
  }
  // main loop
  while (1) {
    // print them on the screen
    print_todos(todo_head);
    // get input from user
    if (get_and_dispatch_input(todo_head))
      break;
  }

  save_todo_items(todo_head);

  return 0;
}
