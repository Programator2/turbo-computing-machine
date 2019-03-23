#include <stdio.h>
#include <time.h>

int read_date(char* buffer, struct tm* tm)
{
  int ret = sscanf(buffer,
		   "%d-%d-%d %*s",
		   &tm->tm_year, &tm->tm_mon, &tm->tm_mday);
  return ret == 3;
}
