#include <stdio.h>
#include <ctype.h>

#include "day3.h"

#define ALPHABET_SIZE 52
#define DAY 2

int part1();
int part2();
int itemToIndex(char type);

main()
{
  int sum =
#if DAY == 1
  part1();
#else
  part2();
#endif

  printf("the total sum of priorities is: %d\n", sum);

  return 0;
}

int part1()
{
  int i, j, k, len, sum;
  char buffer[ALPHABET_SIZE*2];
  char* compartment1, *compartment2;

  compartment1 = buffer;
  compartment2 = buffer + ALPHABET_SIZE;
  sum = 0;

  for (i = 0; i < (sizeof(data)/sizeof(data[0])); ++i)
  {
    memset(buffer, 0, sizeof(buffer));

    len = strlen(data[i]) / 2;
    for (j = 0, k = len; j < len; ++j, ++k)
    {
      compartment1[itemToIndex(data[i][j])] = 1;
      compartment2[itemToIndex(data[i][k])] = 1;
    }

    for (j = 0; j < ALPHABET_SIZE; ++j)
    {
      if ((compartment1[j] + compartment2[j]) > 1)
      {
	sum += j + 1;
      }
    }
  }

  return sum;
}

void analyzeRucksack(char* buffer, const char* data, int index)
{
  int i, len = strlen(data);
  for (i = 0; i < len; ++i)
  {
    buffer[itemToIndex(data[i])] |= (1 << index);
  }
}

int part2()
{
  int i, j, sum;
  char buffer[ALPHABET_SIZE];

  sum = 0;

  for (i = 0; i < (sizeof(data)/sizeof(data[0])); i += 3)
  {
    memset(buffer, 0, sizeof(buffer));

    analyzeRucksack(buffer, data[i+0], 0);
    analyzeRucksack(buffer, data[i+1], 1);
    analyzeRucksack(buffer, data[i+2], 2);

    for (j = 0; j < ALPHABET_SIZE; ++j)
    {
      if (buffer[j] == 7)
      {
	sum += j + 1;
      }
    }
  }

  return sum;
}

int itemToIndex(char type)
{
  if (isupper(type)) {
    return type - 'A' + 26;
  }

  return type - 'a';
}