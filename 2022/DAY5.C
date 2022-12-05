#include <stdio.h>
#include <alloc.h>

#include "day5.h"

#define NUM_STACKS 9
#define MAX_STACK_DEPTH 64
#define DAY 2

void parseStack();
int pop(int stackIndex);
int peek(int stackIndex, int index);
void push(int stackIndex, int value);

char stack[NUM_STACKS*MAX_STACK_DEPTH];
int stackCount[NUM_STACKS];

main()
{
  int i, j, count, index1, index2;

  clrscr();

  parseStack();

  for (i = 0; i < (sizeof(data)/sizeof(data[0])); ++i)
  {
    sscanf(data[i], "move %d from %d to %d", &count, &index1, &index2);

    index1 -= 1;
    index2 -= 1;

#if DAY == 1
    for (j = 0; j < count; ++j)
    {
      push(index2, pop(index1));
    }
#else
    for (j = count - 1; j >= 0; --j)
    {
      push(index2, peek(index1, j));
    }
    stackCount[index1] -= count;
#endif
  }

  for (i = 0; i < NUM_STACKS; ++i)
  {
    printf("%c", pop(i));
  }

  return 0;
}

void parseStack()
{
  int i, j;
  const char* p;

  for (i = (sizeof(stacks)/sizeof(stacks[0]))-1; i >= 0; --i)
  {
    p = stacks[i];
    for (j = 0; *p; ++p, ++j)
    {
      if (*p == '[')
      {
	push(j / 4, p[1]);
      }
    }
  }
}

int pop(int stackIndex)
{
  int count = stackCount[stackIndex] - 1;
  int result = stack[stackIndex*MAX_STACK_DEPTH+count];
  stackCount[stackIndex] = count;
  return result;
}

int peek(int stackIndex, int index)
{
  int count = stackCount[stackIndex] - 1;
  return stack[stackIndex*MAX_STACK_DEPTH + count - index];
}

void push(int stackIndex, int value)
{
  int count = stackCount[stackIndex];
  stack[stackIndex*MAX_STACK_DEPTH+count] = value;
  stackCount[stackIndex] = count + 1;
  if (count > MAX_STACK_DEPTH-1)
  {
    printf("stack full %d (%d)\n", stackIndex, count);
    exit(0);
  }
}