#ifndef TODO_DATE_H
#define TODO_DATE_H

#include <time.h>

#define MAKE_DATE_INVALID(tm) (tm)->tm_mday = 0

#define IS_DATE_INVALID(tm) (tm)->tm_mday == 0

/**
 * @brief Converts date from a string to a @t tm structure.
 *
 * Converts date in a format 2019-04-01 to @c tm structure.
 *
 * @param buffer Null-terminated string containing the date.
 * @param tm Pointer to @c tm structure, which will be filled.
 */
int read_date(char* buffer, struct tm* tm);

#endif /* TODO_DATE_H */
