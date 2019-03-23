#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "date.h"

struct todo_item {
  struct todo_item* prev;
  struct todo_item* next;
  
  bool done;
  char priority;
  struct tm completion_tm;
  struct tm creation_tm;
  char* description;
};

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
    position += 3;
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
  memcpy(todo->description, buffer+position, description_length+1);

  return 0;
}
