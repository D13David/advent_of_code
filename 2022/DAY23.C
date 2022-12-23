#include <stdio.h>

#include "day23.h"

#define DAY 2

#define MAX_ELVES 2000
#if DAY == 1
#define STEPS 10
#else
#define STEPS 99999
#endif

typedef struct vec2
{
	int x, y;
} vec2_t;

typedef struct move
{
	vec2_t* elve;
	vec2_t moveTo;
} move_t;

vec2_t elves[MAX_ELVES];
int numElves;

move_t moves[MAX_ELVES];
int numMoves;

void parseData();
vec2_t* findElve(int x, int y);
void findBounds(vec2_t* min, vec2_t* max);
int calcTiles();

main()
{
	int i, j, k, dirIndex = 0, numAdj, *dir;
	vec2_t* elve, min, max;
	move_t* move;
	int adj[8];

	const int searchDirection[] =
	{
		1, 0, 2,
		6, 5, 7,
		3, 0, 5,
		4, 2, 7
	};

	const vec2_t direction[] =
	{
		{-1,-1}, {0,-1}, {1,-1},
		{-1, 0},	     {1, 0},
		{-1, 1}, {0, 1}, {1, 1}
	};

	parseData();

	for (i = 0; i < STEPS; ++i)
	{
		for (j = 0; j < numElves; ++j)
		{
			elve = &elves[j];
			numAdj = 0;

			for (k = 0; k < 8; ++k)
			{
				adj[k] = findElve(elve->x + direction[k].x, elve->y + direction[k].y) != NULL;
				if (adj[k] == 0) {
					++numAdj;
				}
			}
			if (numAdj == 8) {
				continue;
			}
			for (k = 0; k < 4; ++k)
			{
				dir = &searchDirection[(dirIndex+k)%4 * 3];
				if (adj[dir[0]] == 0 && adj[dir[1]] == 0 && adj[dir[2]] == 0)
				{
					move = &moves[numMoves++];
					move->elve = elve;
					move->moveTo.x = elve->x + direction[dir[0]].x;
					move->moveTo.y = elve->y + direction[dir[0]].y;
					break;
				}
			}
		}

#if DAY == 2
		if (numMoves == 0) {
			break;
		}
#endif

		for (j = 0; j < numMoves; ++j)
		{
			move = &moves[j];

			for (k = 0; k < numMoves; ++k)
			{
				if (k == j) continue;
				if (moves[k].moveTo.x == move->moveTo.x && moves[k].moveTo.y == move->moveTo.y) {
					break;
				}
			}

			if (k >= numMoves)
			{
				move->elve->x = move->moveTo.x;
				move->elve->y = move->moveTo.y;
			}
		}

		numMoves = 0;
		dirIndex = (dirIndex + 1) % 4;
	}

	findBounds(&min, &max);

#if DAY == 1
	printf("%d\n", calcTiles());
#else
	printf("%d\n", i+1);
#endif
	
	return 0;
}

void findBounds(vec2_t* min, vec2_t* max)
{
	int i;

	min->x = 99999; min->y = 99999;
	max->x = -99999; max->y = -99999;
	for (i = 0; i < numElves; ++i)
	{
		if (elves[i].x < min->x) min->x = elves[i].x;
		if (elves[i].y < min->y) min->y = elves[i].y;
		if (elves[i].x > max->x) max->x = elves[i].x;
		if (elves[i].y > max->y) max->y = elves[i].y;
	}
}

int calcTiles()
{
	int x, y, emptyTiles = 0;
	vec2_t min, max;
	findBounds(&min, &max);

	for (y = min.y; y <= max.y; ++y)
	{
		for (x = min.x; x <= max.x; ++x)
		{
			if (!findElve(x, y)) ++emptyTiles;
		}
	}
	return emptyTiles;
}

vec2_t* findElve(int x, int y)
{
	int i;

	for (i = 0; i < numElves; ++i)
	{
		if (elves[i].x == x && elves[i].y == y) {
			return &elves[i];
		}
	}
	return NULL;
}

void parseData()
{
	int i, j;
	vec2_t* elve;

	for (i = 0; i < (sizeof(data) / sizeof(data[0])); ++i)
	{
		for (j = 0; j < strlen(data[i]); ++j)
		{
			if (data[i][j] == '.') {
				continue;
			}

			elve = &elves[numElves++];
			elve->x = j;
			elve->y = i;
		}
	}
}