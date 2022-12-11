#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "day11.h"

#define DAY 2
#define MAX_ITEMS 64
#define NUM_MONKEYS 8
#if DAY == 1
#define NUM_ROUNDS 20
#else
#define NUM_ROUNDS 10000
#endif

typedef enum
{
  Plus, Times, Square
} op;

typedef struct monkey_t
{
  long long items[MAX_ITEMS];
  int numItems;
  op operation;
  int value;
  int condition;
  int targets[2];
} monkey;

void playMonkey(monkey* monkey);
void parseMonkeys();
int cmp(const void* a, const void* b);

monkey g_monkeys[NUM_MONKEYS];
long g_modulo;

main()
{
  int i, j;
  long inspections[NUM_MONKEYS];

  parseMonkeys();

  memset(inspections, 0, sizeof(inspections));

  for (i = 0; i < NUM_ROUNDS; ++i)
  {
    for (j = 0; j < NUM_MONKEYS; ++j)
    {
      inspections[j] += g_monkeys[j].numItems;
      playMonkey(&g_monkeys[j]);
    }
  }

  qsort(inspections, NUM_MONKEYS, sizeof(inspections[0]), cmp);

  printf("%lld\n", (long long)inspections[0] * inspections[1]);

  return 0;
}

void playMonkey(monkey* monkey)
{
  int i;
  long long item;
  struct monkey_t* target = NULL;

  for (i = 0; i < monkey->numItems; ++i)
  {
    item = monkey->items[i];
    if (monkey->operation == Plus)
    {
      item += monkey->value;
    }
    else if (monkey->operation == Times)
    {
      item *= monkey->value;
    }
    else
    {
      item = item * item;
    }
#if DAY == 1
    item /= 3;
#else
    item %= g_modulo;
#endif
    if ((item % monkey->condition) == 0)
    {
      target = &g_monkeys[monkey->targets[0]];
    }
    else
    {
      target = &g_monkeys[monkey->targets[1]];
    }
    assert(target->numItems < MAX_ITEMS);
    target->items[target->numItems++] = item;
  }

  monkey->numItems = 0;
}

void parseMonkeys()
{
  int i, id;
  char buffer[64];
  const char* p;
  monkey* current;

  g_modulo = 1;

  for (i = 0; i < (sizeof(data)/sizeof(data[0])); )
  {
    // monkey id
    sscanf(data[i], "Monkey %d:", &id), ++i;
    current = &g_monkeys[id];

    // item list
    strcpy(buffer, data[i] + 18 /*offset to first number*/), ++i;
    p = strtok(buffer, ",");
    for (current->numItems = 0; p; ++current->numItems)
    {
      current->items[current->numItems] = atoi(p);
      p = strtok(NULL, ",");
    }

    // operation
    sscanf(data[i], "  Operation: new = %s %c %s", &buffer[0], &buffer[4], &buffer[5]), ++i;

    if (!strcmp(&buffer[5], "old"))
    {
      current->operation = Square;
    }
    else
    {
      if (buffer[4] == '*') current->operation = Times;
      else current->operation = Plus;
      current->value = atoi(&buffer[5]);
    }

    // condition & targets
    sscanf(data[i], "  Test: divisible by %d", &current->condition), ++i;
    sscanf(data[i], "    If true: throw to monkey %d", &current->targets[0]), ++i;
    sscanf(data[i], "    If false: throw to monkey %d", &current->targets[1]), ++i;

    g_modulo *= current->condition;
  }
}

int cmp(const void* a, const void* b)
{
  return *((const int*)b) - *((const int*)a);
}