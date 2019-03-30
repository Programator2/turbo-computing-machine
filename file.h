#ifndef TODO_FILE_H
#define TODO_FILE_H

#include <stdio.h>

FILE* open_todo_file(void);
FILE* open_todo_file_for_writing(void);
void close_todo_file(FILE* file);
void close_todo_file_for_writing(FILE* file);
char* read_line(FILE* file);
int write_line(FILE* file, char* buffer);

#endif /* TODO_FILE_H */
