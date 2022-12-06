#include <stdio.h>

#include "day6.h"

#define DAY 2

#if DAY == 1
#define SLIDING_WINDOW_SIZE 4
#else
#define SLIDING_WINDOW_SIZE 14
#endif

main()
{
  int i, j, offset, len;

  clrscr();

  len = strlen(data);

  for (i = 0, offset = 0; i < len; ++i)
  {
    for (j = i-1; j >= offset; --j)
    {
      if (data[j] == data[i])
      {
	offset = j;
	break;
      }
    }
    if (i - offset >= SLIDING_WINDOW_SIZE) {
      break;
    }
  }

  printf("%d\n", i+1);

  return 0;
}