#ifndef TODO_DATE_H
#define TODO_DATE_H

#include <time.h>

#define MAKE_DATE_INVALID(tm) (tm)->tm_mday = 0

#define IS_DATE_INVALID(tm) (tm)->tm_mday == 0

int read_date(char* buffer, struct tm* tm);

#endif /* TODO_DATE_H */
