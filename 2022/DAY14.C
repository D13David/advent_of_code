#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include <assert.h>

#include "DAY14.H"

#define MAX_PATH_LENGTH 32
#define MAX_WIDTH 670
#define MAX_HEIGHT 164

#define STARTX 500
#define STARTY 0

#define DAY 2

typedef enum { false, true } bool;

typedef struct point
{
	int x, y;
} point_t;

char* world;

int parsePath(const char* data, point_t* path);
void rasterLine(int x0, int y0, int x1, int y1);
bool traceSandGrain(void);

main()
{
	int i, j, pathLength;
	long sum = 0;
	point_t path[MAX_PATH_LENGTH], prev, next;

	world = malloc(MAX_WIDTH*MAX_HEIGHT);
	assert(world != NULL);
	memset(world, 0, MAX_WIDTH * MAX_HEIGHT);

	for (i = 0; i < (sizeof(data) / sizeof(data[0])); ++i)
	{
		pathLength = parsePath(data[i], path);

		prev = path[0];
		for (j = 1; j < pathLength; ++j)
		{
			next = path[j];
			rasterLine(prev.x, prev.y, next.x, next.y);
			prev = next;
		}
	}

	while (true)
	{
		if (!traceSandGrain())
			break;

		++sum;
	}

	printf("%ld units of sand where spawned\n", sum);

	free(world);

	return 0;
}

int parsePath(const char* data, point_t* path)
{
	int count = 0;
	char buffer[512];
	const char* p;

	strcpy(buffer, data);
	p = strtok(buffer, " -> ");
	while (p)
	{
		sscanf(p, "%d,%d", &path->x, &path->y);
		p = strtok(NULL, " -> ");
		++count;
		assert(count < MAX_PATH_LENGTH);
		++path;
	}

	return count;
}

void rasterLine(int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;

	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;

	int err = dx + dy, e2;

	while (1)
	{
		world[y0 * MAX_WIDTH + x0] = '#';

		if (x0 == x1 && y0 == y1) {
			break;
		}

		e2 = 2 * err;

		if (e2 > dy) {
			err += dy;
			x0 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y0 += sy;
		}
	}
}

char getObjectFromWorld(int x, int y)
{
	return world[y * MAX_WIDTH + x];
}

void setObjectInWorld(int x, int y, char obj)
{
	world[y * MAX_WIDTH + x] = obj;
}

bool traceSandGrain(void)
{
	int x = STARTX, y = STARTY, ny;

	while (true)
	{
		ny = y + 1;

#if DAY == 1
		if (ny >= MAX_HEIGHT)
#else
		if (getObjectFromWorld(STARTX, STARTY) == 'o')
#endif
		{
			return false;
		}

#if DAY == 2
		if (ny >= MAX_HEIGHT-1) {
			setObjectInWorld(x, y, 'o');
			break;
		}
#endif

		if (getObjectFromWorld(x, ny) == 0)
		{
			y = ny;
		}
		else if (getObjectFromWorld(x - 1, ny) == 0)
		{
			x = x - 1;
			y = ny;
		}
		else if (getObjectFromWorld(x + 1, ny) == 0)
		{
			x = x + 1;
			y = ny;
		}
		else
		{
			setObjectInWorld(x, y, 'o');
			break;
		}
	}

	return true;
}