#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "date.h"
#include "file.h"
#include "list.h"
#include "todo.h"

struct todo_item* new_todo_item(void)
{
  return (struct todo_item*) calloc(1, sizeof(struct todo_item));
}

void free_todo_item(struct todo_item* todo)
{
  free(todo);
}

int parse_todo_item(char* buffer, struct todo_item* todo)
{
  int position = 0;
  int description_length;

  if (buffer[position] == 'x' &&
      buffer[position+1] == ' ') {
    todo->done = true;
    position += 2;
  }

  if (buffer[position] == '(' &&
      buffer[position+2] == ')' &&
      buffer[position+3] == ' ') {
    todo->priority = buffer[position+1];
    position += 4;
  }

  if (isdigit(buffer[position])) {
    if (todo->done) {
      if (read_date(buffer+position, &todo->completion_tm))
	return -1;

      // move to the possible creation date
      position += 11;
    }

    if (read_date(buffer+position, &todo->creation_tm))
      MAKE_DATE_INVALID(&todo->creation_tm);
    else
      position += 11;
  }

  description_length = strlen(buffer+position);
  todo->description = (char*) malloc((description_length+1)*sizeof(char));
  if (todo->description == NULL)
    return -ENOMEM;
  memcpy(todo->description, buffer+position, description_length-1);
  todo->description[description_length-1] = '\0';

  return 0;
}

void insert_todo_item(struct todo_item* head, struct todo_item* new)
{
  if (!new->priority) {
    // put it to the end of the list
    while (head->next)
      head = head->next;
    insert_after(head, new);
    return;
  }
  while (head->priority && head->priority <= new->priority) {
    if (!head->next) {
      insert_after(head, new);
      return;
    }
    head = head->next;
  }
  insert_before(head, new);
  return;
}

struct todo_item* load_todo_items(void)
{
  char* line;
  struct todo_item *head_todo = NULL, *iter_todo = NULL, *old_todo;
  bool inconsistent = false;

  FILE* file = open_todo_file();
  if (!file)
    return NULL;

  iter_todo = head_todo;

  while ((line = read_line(file))) {
    old_todo = iter_todo;
    iter_todo = new_todo_item();
    if (!iter_todo) {
      close_todo_file(file);
      return NULL;
    }

    if (parse_todo_item(line, iter_todo)) {
      inconsistent = true;
      free_todo_item(iter_todo);
      continue;
    }

    if (!head_todo) {
      head_todo = iter_todo;
      continue;
    }

    insert_after(old_todo, iter_todo);
  }

  close_todo_file(file);

  if (inconsistent)
    puts("Warning! Some todo.txt entries are invalid. Check them before quitting.");

  return head_todo;
}

char* todo_item_to_str(struct todo_item* todo)
{
  static char* buffer;
  char* new_buffer;
  static size_t buffer_size;
  int position = 0;
  int bytes_written;

  if (!buffer) {
    buffer_size = 128;
    buffer = (char*) malloc(buffer_size*sizeof(char));
    if (!buffer)
      return NULL;
  }

  if (todo->done) {
    buffer[position++] = 'x';
    buffer[position++] = ' ';
  }

  if (todo->priority) {
    buffer[position++] = '(';
    buffer[position++] = todo->priority;
    buffer[position++] = ')';
    buffer[position++] = ' ';
  }

  if (!IS_DATE_INVALID(&todo->completion_tm)){
    bytes_written = strftime(buffer+position,
			     buffer_size-position,
			     "%Y-%m-%d ",
			     &todo->completion_tm);
    if (!bytes_written)
      return NULL;
    position += bytes_written;
  }

  if (!IS_DATE_INVALID(&todo->creation_tm)){
    bytes_written = strftime(buffer+position,
			     buffer_size-position,
			     "%Y-%m-%d ",
			     &todo->creation_tm);
    if (!bytes_written)
      return NULL;
    position += bytes_written;
  }

  while ((strlen(todo->description) + position + 1) > buffer_size) {
    new_buffer = (char*) realloc(buffer, buffer_size*2*sizeof(char));
    if (new_buffer == NULL)
      return NULL;
    buffer_size *= 2;
    buffer = new_buffer;
  }

  memcpy(buffer+position, todo->description, strlen(todo->description)+1);

  return buffer;
}

int save_todo_items(struct todo_item* head)
{
  char* buffer;
  struct todo_item* iter;
  FILE* todo_file = open_todo_file_for_writing();

  if (!todo_file)
    return -1;

  iter = head;

  while (iter) {
    buffer = todo_item_to_str(iter);
    if (!buffer) {
      close_todo_file_for_writing(todo_file);
      return -1;
    }
    if (write_line(todo_file, buffer))
      return -1;
    iter = iter->next;
  }

  close_todo_file_for_writing(todo_file);
    // komentar
  return 0;
}
