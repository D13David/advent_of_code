#include <stdio.h>
#include <string.h>

#include "day4.h"

#define DAY 2

typedef enum { false, true } bool;

void parseRange(const char* input, int* range);
bool contains(int rage1[2], int range2[2]);

main()
{
  int i, sum, range1[2], range2[2];

  clrscr();

  for (i = 0, sum = 0; i < (sizeof(data)/sizeof(data[0])); i += 2)
  {
    parseRange(data[i], range1);
    parseRange(data[i+1], range2);

#if DAY == 1
    if (contains(range1, range2) || contains(range2, range1))
#else
    if (range1[1] >= range2[0] && range1[0] <= range2[1])
#endif
    {
      sum++;
    }
  }

  printf("result true for %d pairs\n", sum);

  return 0;
}

void parseRange(const char* input, int* range)
{
  char buffer[512];
  char* p;

  strcpy(buffer, input);
  p = strtok(buffer, "-");
  *range++ = atoi(p);
  p = strtok(NULL, ",-");
  *range++ = atoi(p);
}

bool contains(int range1[2], int range2[2])
{
  if (range1[0] <= range2[0] && range1[1] >= range2[1]) {
    return true;
  }
  return false;
}