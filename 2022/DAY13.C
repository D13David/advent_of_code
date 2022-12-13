#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "DAY13.H"

#define NUM_ELEMENTS (sizeof((data)) / sizeof((data)[0]))

#define ITEM_TYPE_ARRAY		 1
#define ITEM_TYPE_NUMBER	 2

#define RESULT_NONE			 0
#define RESULT_NOT_IN_ORDER	-1
#define RESULT_IN_ORDER		 1

#define PAIR_INDEX_LEFT		 0
#define PAIR_INDEX_RIGHT	 1

#define MAX_ARRAY_SIZE		20

#define DAY 2

typedef enum { false, true } bool;

typedef struct span_t
{
	const char* first, *last;
} span;

typedef struct element_t
{
	int type;
	span span;
	int number;
} element;

int parseElement(element* element, const char** it)
{
	int depth;
	bool hasElements = true;
	const char* p = *it;
	
	element->span.first = p + 1;

	if (*p == '[')
	{
		element->type = ITEM_TYPE_ARRAY;
		for (depth = 1, p = p + 1; depth > 0; ++p)
		{
			if (*p == '[') ++depth;
			if (*p == ']') --depth;
		}
	}
	else if (*p == ']')
	{
		hasElements = false; // empty array
	}
	else
	{
		element->type = ITEM_TYPE_NUMBER;
		element->number = atoi(p);
		while (*p != ',' && *p != ']')
			++p;
	}

	element->span.last = p++;
	*it = p;
	return hasElements;
}

int compare(span span1, span span2)
{
	int i, result, numElementsLeft, numElementsRight, numElementsToCheck;
	element elementsLeft[MAX_ARRAY_SIZE], elementsRight[MAX_ARRAY_SIZE];
	const char* p;
	char buffer[16];

	numElementsLeft = 0;
	numElementsRight = 0;

	for (p = span1.first; p != span1.last;) {
		numElementsLeft += parseElement(&elementsLeft[numElementsLeft], &p);
	}

	for (p = span2.first; p != span2.last;) {
		numElementsRight += parseElement(&elementsRight[numElementsRight], &p);
	}

	numElementsToCheck = numElementsLeft;
	if (numElementsToCheck < numElementsRight) {
		numElementsToCheck = numElementsRight;
	}

	for (i = 0; i < numElementsToCheck; ++i)
	{
		if (i >= numElementsLeft) {
			return RESULT_IN_ORDER;
		}
		if (i >= numElementsRight) {
			return RESULT_NOT_IN_ORDER;
		}
		if (elementsLeft[i].type == ITEM_TYPE_NUMBER && elementsRight[i].type == ITEM_TYPE_NUMBER)
		{
			if (elementsLeft[i].number > elementsRight[i].number) {
				return RESULT_NOT_IN_ORDER;
			}

			if (elementsLeft[i].number < elementsRight[i].number) {
				return RESULT_IN_ORDER;
			}
		} 
		else
		{
			// promote element to array
			if (elementsLeft[i].type == ITEM_TYPE_NUMBER) {
				sprintf(buffer, "%d]", elementsLeft[i].number);
				elementsLeft[i].span.first = buffer;
				elementsLeft[i].span.last = elementsLeft[i].span.first + strlen(buffer);
				elementsLeft[i].type = ITEM_TYPE_ARRAY;

			}
			if (elementsRight[i].type == ITEM_TYPE_NUMBER) {
				sprintf(buffer+5, "%d]", elementsRight[i].number);
				elementsRight[i].span.first = buffer+5;
				elementsRight[i].span.last = elementsRight[i].span.first + strlen(buffer + 5);
				elementsRight[i].type = ITEM_TYPE_ARRAY;
			}

			result = compare(elementsLeft[i].span, elementsRight[i].span);
			if (result != RESULT_NONE) {
				return result;
			}
		}
	}

	return RESULT_NONE;
}

int cmp(const void* a, const void* b)
{
	int index0 = *(const int*)a;
	int index1 = *(const int*)b;
	span span1, span2;
	span1.first = data[index0]; span1.last = data[index0] + strlen(data[index0]) + 1;
	span2.first = data[index1]; span2.last = data[index1] + strlen(data[index1]) + 1;
	return -compare(span1, span2);
}

main()
{
	int i, p1, p2, sum = 0;
	span span1, span2;
	int indices[NUM_ELEMENTS];

#if DAY == 1
	for (i = 0; i < NUM_ELEMENTS; i += 2)
	{
		span1.first = data[i]; span1.last = data[i] + strlen(data[i]) + 1;
		span2.first = data[i+1]; span2.last = data[i+1] + strlen(data[i+1]) + 1;
		if (compare(span1, span2) == RESULT_IN_ORDER) {
			sum += (i / 2) + 1;
		}
	}

	printf("%d\n", sum);
#else
	for (i = 0; i < NUM_ELEMENTS; ++i) {
		indices[i] = i;
	}

	qsort(indices, NUM_ELEMENTS, sizeof(indices[0]), cmp);

	for (i = 0; i < NUM_ELEMENTS; ++i)
	{
		if (!strcmp(data[indices[i]], "[[2]]")) {
			p1 = i+1;
		}
		else if (!strcmp(data[indices[i]], "[[6]]")) {
			p2 = i+1;
		}
	}

	printf("%d\n", p1 * p2);
#endif

	return 0;
}