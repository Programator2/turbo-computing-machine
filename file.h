#ifndef TODO_FILE_H
#define TODO_FILE_H

#include <stdio.h>

/**
 * @brief Opens todo file.
 *
 * Open todo.txt file in the working directory. It also allocates buffer for
 * reading the todo file if it's not already allocated.
 *
 * @return @c FILE handle to the opened file, NULL if opening of the fil was
 * not succesful or if allocation of the buffer was not succesful.
 */
FILE* open_todo_file(void);

/**
 * @brief Opens todo file for writing.
 *
 * Opens file todo.txt in the working directory for writing. Original file
 * contents are not saved.
 *
 * @return @c FILE handle to the opened file, @c NULL if the opening was not
 * successful.
 */
FILE* open_todo_file_for_writing(void);

/**
 * @brief Closes todo file.
 *
 * Closes todo file previously opened by @c open_todo_file() function.
 * The previously allocated buffer for reading the file contents is also
 * freed.
 *
 * @param file @c FILE handle to an opened todo file.
 */
void close_todo_file(FILE* file);

/**
 * @brief Closes todo file opened for writing.
 *
 * Closes todo file previously opened by @c open_todo_file_for_writing()
 * function.
 *
 * @param file @c FILE handle to an opened todo file.
 */
void close_todo_file_for_writing(FILE* file);

/**
 * @brief Reads a line from the @c file.
 *
 * Reads a line from previously opened todo file passed as the argument.
 *
 * @param file @c FILE handle to the todo file.
 * @return Null terminated string containing the line. NULL if @c EOF was
 * reached or if the buffer couldn't be reallocated.
 */
char* read_line(FILE* file);

/**
 * @brief Writes a line to a file.
 *
 * @param file @c FILE handle of file opened for witing.
 * @param buffer Null terminated string to be written to the file.
 * @return 0 on success, -1 otherwise.
 */
int write_line(FILE* file, char* buffer);

#endif /* TODO_FILE_H */
