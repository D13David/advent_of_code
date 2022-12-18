#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>

#include "day18.h"

#define DAY 2

typedef struct voxel
{
	int x, y, z;
} voxel_t;

#define NUM_VOXELS (sizeof(data)/sizeof(data[0]))

#define WORLD_WIDTH 21
#define WORLD_HEIGHT 21
#define WORLD_DEPTH 21

#define MAX_STACK_SIZE 65535

#define ROCK 1
#define WATER 2

void setValueAt(int x, int y, int z, int value);
int getValueAt(int x, int y, int z);
void push(voxel_t value);
voxel_t pop();
int count();
int min(int a, int b);
int max(int a, int b);

char* world;
voxel_t stack[MAX_STACK_SIZE];
int stackIndex;

main()
{
	int i, j, k, coord[3];
	int sum;
	voxel_t v1, v2;

	world = (char*)malloc(WORLD_WIDTH * WORLD_HEIGHT * WORLD_DEPTH);
	memset(world, 0, WORLD_WIDTH * WORLD_HEIGHT * WORLD_DEPTH);

	for (i = 0; i < NUM_VOXELS; i += 3)
	{
		setValueAt(data[i + 0], data[i + 1], data[i + 2], ROCK);
	}

#if DAY == 2
	v1.x = WORLD_WIDTH-1;
	v1.y = WORLD_HEIGHT-1;
	v1.z = WORLD_DEPTH-1;
	push(v1);

	while (count() > 0)
	{
		v2 = pop();

		setValueAt(v2.x, v2.y, v2.z, WATER);

		for (i = 0; i < 3; ++i)
		{
			coord[0] = v2.x;
			coord[1] = v2.y;
			coord[2] = v2.z;
			for (j = -1; j <= 2; j += 3)
			{
				coord[i] += j;
				if (coord[i] >= 0 && coord[i] < WORLD_WIDTH) {
					if (getValueAt(coord[0], coord[1], coord[2]) == 0)
					{
						v1.x = coord[0]; v1.y = coord[1]; v1.z = coord[2];
						setValueAt(v1.x, v1.y, v1.z, WATER);
						push(v1);
					}
				}
			}
		}
	}
#endif

	for (i = 0, sum = 0; i < NUM_VOXELS; i += 3)
	{
		for (j = 0; j < 3; ++j)
		{
			coord[0] = data[i + 0];
			coord[1] = data[i + 1];
			coord[2] = data[i + 2];
			for (k = -1; k < 2; k += 2)
			{
				coord[j] = data[i+j] + k;
				if (coord[j] >= 0 && coord[j] < WORLD_WIDTH) {
#if DAY == 1
					if (getValueAt(coord[0], coord[1], coord[2]) != ROCK) sum++;
#else
					if (getValueAt(coord[0], coord[1], coord[2]) == WATER) sum++;
#endif
				}
				else
				{
					++sum;
				}
			}
		}
	}

	printf("surface size is %d\n", sum);

	free(world);

	return 0;
}

void setValueAt(int x, int y, int z, int value)
{
	world[z * WORLD_WIDTH * WORLD_HEIGHT + y * WORLD_WIDTH + x] = value;
}

int getValueAt(int x, int y, int z)
{
	return world[z * WORLD_WIDTH * WORLD_HEIGHT + y * WORLD_WIDTH + x];
}

void push(voxel_t value)
{
	assert(stackIndex < MAX_STACK_SIZE);
	stack[stackIndex++] = value;
}

voxel_t pop()
{
	assert(stackIndex > 0);
	return stack[--stackIndex];
}

int count()
{
	return stackIndex;
}

int min(int a, int b)
{
	if (a < b) return a;
	return b;
}

int max(int a, int b)
{
	if (a > b) return a;
	return b;
}