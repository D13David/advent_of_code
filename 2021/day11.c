#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define PART 2

int data1[] =
{
	4,7,6,4,7,4,5,7,8,4,
	4,6,4,3,4,5,7,1,7,6,
	8,3,2,2,6,2,8,4,7,7,
	7,6,1,7,1,5,2,5,4,6,
	6,1,3,7,5,1,8,1,6,5,
	1,5,5,6,7,2,3,1,7,6,
	2,1,8,7,8,6,1,8,8,6,
	2,5,5,3,4,2,2,6,2,5,
	4,8,1,7,5,8,4,6,3,8,
	3,7,5,4,2,8,5,6,6,2,
};

int data2[] =
{
	5,4,8,3,1,4,3,2,2,3,
	2,7,4,5,8,5,4,7,1,1,
	5,2,6,4,5,5,6,1,7,3,
	6,1,4,1,3,3,6,1,4,6,
	6,3,5,7,3,8,5,4,7,8,
	4,1,6,7,5,2,4,6,4,5,
	2,1,7,6,8,4,1,7,2,1,
	6,8,8,2,8,8,1,1,3,4,
	4,8,4,6,8,4,8,5,5,4,
	5,2,8,3,7,5,1,5,2,6,
};

#define data data1
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 10

void flash(int index, int** neighbours, int* flashes)
{
	data[index] = -99999;

	(*flashes)++;

	int* nindex = neighbours[index];
	for (int j = 0; j < 9; ++j)
	{
		int neighbour = nindex[j];
		if (neighbour >= 0)
		{
			int value = ++data[neighbour];
			if (value > 9)
				flash(neighbour, neighbours, flashes);
		}
	}
}

int main()
{
	int** neighbours = (int**)malloc(BOARD_WIDTH * BOARD_HEIGHT * sizeof(int*));
	assert(neighbours != NULL && "allocation failed");

	for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; ++i)
	{
		int x = i % BOARD_WIDTH;
		int y = i / BOARD_WIDTH;

		neighbours[i] = (int*)malloc(9 * sizeof(int));
		assert(neighbours[i] != NULL && "allocation failed");
		for (int j = 0; j < 9; ++j)
			neighbours[i][j] = -1;


		int numNeighbors = 0;
		if (x > 0)
			neighbours[i][numNeighbors++] = y * BOARD_WIDTH + x - 1;
		if (x < BOARD_WIDTH - 1)
			neighbours[i][numNeighbors++] = y * BOARD_WIDTH + x + 1;
		if (y > 0)
			neighbours[i][numNeighbors++] = (y - 1) * BOARD_WIDTH + x;
		if (y < BOARD_HEIGHT - 1)
			neighbours[i][numNeighbors++] = (y + 1) * BOARD_WIDTH + x;
		if (x > 0 && y > 0)
			neighbours[i][numNeighbors++] = (y - 1) * BOARD_WIDTH + x - 1;
		if (x > 0 && y < BOARD_HEIGHT - 1)
			neighbours[i][numNeighbors++] = (y + 1) * BOARD_WIDTH + x - 1;
		if (x < BOARD_WIDTH - 1 && y > 0)
			neighbours[i][numNeighbors++] = (y - 1) * BOARD_WIDTH + x + 1;
		if (x < BOARD_WIDTH - 1 && y < BOARD_HEIGHT - 1)
			neighbours[i][numNeighbors++] = (y + 1) * BOARD_WIDTH + x + 1;
	}

	int flashes = 0;
	int step = 0;

#if PART == 1
	for (step = 0; step < 100; ++step)
#else
	for (bool allZero = false; !allZero; ++step)
#endif
	{
		for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; ++i)
		{
			data[i]++;
		}
		for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; ++i)
		{
			if (data[i] >= 10)
			{
				flash(i, neighbours, &flashes);
			}
		}
		for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; ++i)
		{
			if (data[i] < 0)
				data[i] = 0;
		}

#if PART == 2
		allZero = true;
		for (int i = 0; allZero && i < BOARD_WIDTH * BOARD_HEIGHT; ++i)
		{
			allZero &= data[i] == 0;
		}
#endif
	}

#if PART == 1
	printf("%d\n", flashes);
#else
	printf("%d\n", step);
#endif

	for (int i = 0; i < 9; ++i)
		free(neighbours[i]);

	free(neighbours);
}