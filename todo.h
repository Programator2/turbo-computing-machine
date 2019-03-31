#ifndef TODO_TODO_H
#define TODO_TODO_H

#include <stdbool.h>
#include <time.h>

/**
 * @brief Structure representing a todo item
 */
struct todo_item {
  struct todo_item* prev;  /**< Previous @c todo_item in the linked list. */
  struct todo_item* next;  /**< Next @c todo_item in the linked list. */

  bool done;               /**< True if the item was completed */
  char priority;           /**< Uppercase letter indicating the priority (the lower character, the higher priority */
  struct tm completion_tm; /**< Date of the completion, if the item was completed */
  struct tm creation_tm;   /**< Date of creation of the item (may be @c NULL) */
  char* description;       /**< Null terminated string containing description of the todo item */
};

/**
 * Allocates a new todo item.
 *
 * @return Pointer to the new odo item, NULL if an item couldn't be allocated.
 */
struct todo_item* new_todo_item(void);

/**
 * @brief Frees a todo item.
 *
 * Free a todo item previously allocated by @c new_todo_item() function.
 *
 * @param todo Pointer to the todo item to be freed.
 */
void free_todo_item(struct todo_item* todo);

/**
 * @brief Loads todo items.
 *
 * Opens todo.txt file, parses its contents and creates a linked list of
 * @c todo_item structures containing information from the file. Items
 * will be sorted based on their priority (if any).
 *
 * @return Pointer to the first todo item.
 */
struct todo_item* load_todo_items(void);

/**
 * @brief Convert todo item to null terminated string.
 *
 * String can be used to represent the todo item in a todo file. The string is
 * static, the second call rewrites the string.
 *
 * @param todo Pointer to the todo item to be converted.
 * @return Pointer to a null terminated string.
 */
char* todo_item_to_str(struct todo_item* todo);

/**
 * @brief Parses todo item in a form of null terminated string.
 *
 * @param buffer Null terminated string with string todo representation to be
 * converted.
 * @param todo Pointer to a to todo item to be filled.
 * @return 0 on success, error code otherwise (-ENOMEM).
 */
int parse_todo_item(char* buffer, struct todo_item* todo);

/**
 * @brief Saves all todo items to a file.
 *
 * Saves all todo files on a linked list to the todo.txt file in the current
 * working directory. Previous file contents are deleted.
 *
 * @param head Pointer to the first todo item in a linked list.
 * @return 0 on success, -1 on success
 */
int save_todo_items(struct todo_item* head);

/**
 * @brief Inserts todo item into a linked list.
 *
 * Todo item is inserted into linked list of todo item to a correct position
 * based on the priority. If there's no priority, it is inserted onto the end
 * of the list.
 *
 * @param head First todo item in the linked list.
 * @param new Todo item to be inserted
 */
void insert_todo_item(struct todo_item* head, struct todo_item* new);

#endif /* TODO_TODO_H */
