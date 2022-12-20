#include <stdio.h>
#include <string.h>
#include <math.h>

#include "day20.h"

#define DAY 2

#define NUM_ITEMS (sizeof(data)/sizeof(data[0]))

typedef struct item
{
	long long value;
	struct item* prev; 
	struct item* next;
} item_t;

void unlinkNode(item_t* item)
{
	item->prev->next = item->next;
	item->next->prev = item->prev;
}

void linkNodeAfter(item_t* item, item_t* target)
{
	item->next = target->next;
	item->prev = target;
	item->next->prev = item;
	target->next = item;
}

main()
{
	int i, j, steps, offset;
	long long decodedValues[NUM_ITEMS], sum;
	item_t buffer[NUM_ITEMS], *item1, *item2;

	memset(buffer, 0, sizeof(buffer));

	for (i = 0; i < NUM_ITEMS; ++i)
	{
#if DAY == 1
		buffer[i].value = data[i];
#else
		buffer[i].value = data[i] * 811589153ull;
#endif
		buffer[i].next = &buffer[(i + 1) % NUM_ITEMS];
		buffer[i].prev = &buffer[(i - 1 + NUM_ITEMS) % NUM_ITEMS];
	}

#if DAY == 1
	steps = 1;
#else
	steps = 10;
#endif

	while (steps-- > 0)
	{
		for (i = 0; i < NUM_ITEMS; ++i)
		{
			item1 = &buffer[i];
			offset = llabs(item1->value) % (NUM_ITEMS - 1);

			if (offset == 0) {
				continue;
			}

			unlinkNode(item1);

			if (data[i] < 0)
			{
				for (item2 = item1, j = 0; j <= offset; ++j) {
					item2 = item2->prev;
				}
			}
			else
			{
				for (item2 = item1, j = 0; j < offset; ++j) {
					item2 = item2->next;
				}
			}

			linkNodeAfter(item1, item2);
		}
	}

	for (item1 = &buffer[0], i = 0; i < NUM_ITEMS; ++i, item1 = item1->next)
	{
		decodedValues[i] = item1->value;
		if (decodedValues[i] == 0) {
			offset = i;
		}
	}

	int indices[3] = { 1000, 2000, 3000 };
	for (i = 0, sum = 0; i < 3; ++i) {
		sum += decodedValues[(offset + indices[i]) % NUM_ITEMS];
	}

	printf("The sum of the grove coordinates is %lld\n", sum);

	return 0;
}