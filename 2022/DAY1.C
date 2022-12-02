#include <stdio.h>
#include <stdlib.h>
#include <mem.h>

#include "day1.h"

#define DAY 2

int cmp(const void* a, const void* b);

int main()
{
  int i, index = 0;
  long sum[255], total;

  sum[0] = 0;

  for (i = 0; i < (sizeof(data)/sizeof(data[0])); ++i)
  {
    if (!strcmp(data[i], ""))
    {
      sum[++index] = 0;
      continue;
    }

    sum[index] += atol(data[i]);
  }

  qsort((void*)sum, index, sizeof(sum[0]), cmp);

  total = sum[0];
#if DAY == 2
  total += sum[1];
  total += sum[2];
#endif

  printf("total of %ld calories\n", total);

  return 0;
}

int cmp(const void* a, const void* b)
{
  long diff = *((long*)a) - *((long*)b);
  if (diff < 0) return 1;
  if (diff > 0) return -1;
  return 0;
}