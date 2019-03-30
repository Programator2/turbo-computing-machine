#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_BUFFER_SIZE 128

char* buffer = NULL;
int buffer_size = 0;

static char* _check_buffer(void)
{
  if (!buffer) {
    buffer = (char*) malloc(INITIAL_BUFFER_SIZE*sizeof(char));
    if (!buffer) {
      return NULL;
    }
    buffer_size = INITIAL_BUFFER_SIZE;
  }
  return buffer;
}

FILE* open_todo_file(void)
{
  FILE* file = fopen("todo.txt", "r");
  if (!_check_buffer() && file) {
    fclose(file);
    return NULL;
  }
  return file;
}

FILE* open_todo_file_for_writing(void)
{
  FILE* file = fopen("todo.txt", "w");
  return file;
}

void close_todo_file_for_writing(FILE* file)
{
  fclose(file);
}

void close_todo_file(FILE* file)
{
  if (buffer)
    free(buffer);
  buffer = NULL;
  fclose(file);
}

char* read_line(FILE* file)
{
  int position = 0;
  char* new_buffer;

  if (!_check_buffer())
    return NULL;
  while (1) {
    if (fgets(buffer+position, buffer_size-position, file) == NULL)
      return NULL;
    if (!strchr(buffer, '\n')) {
      position = buffer_size-1;
      new_buffer = (char*) realloc(buffer, buffer_size*2*sizeof(char));
      if (new_buffer == NULL)
	    return NULL;
      buffer_size *= 2;
      buffer = new_buffer;
    } else {
      return buffer;
    }
  }
}

int write_line(FILE* file, char* buffer)
{
  if (fputs(buffer, file) < 0)
    return -1;
  if (fputc('\n', file) == EOF)
    return -1;
  return 0;
}
