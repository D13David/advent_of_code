#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "day22.h"

#define DAY 2

#define WIDTH 150
#define HEIGHT 200
#define TILE_WIDTH 50

typedef enum dir
{
	R, D, L, U
} dir_t;

typedef struct worldInfo
{
	int offset, width;
} worldInfo_t;

typedef enum edgeTypeMask
{
	NONE	= 0, 
	LEFT	= 0x01, 
	TOP		= 0x02, 
	RIGHT	= 0x04, 
	BOTTOM	= 0x08, 
	INV		= 0x10
} edgeTypeMask_t;

#define EDGE_TYPE_MASK_EDGE_ONLY 0xf

#define EDGE_INVALID   -1
#define EDGE_LEFT		0
#define EDGE_TOP		1
#define EDGE_RIGHT		2
#define EDGE_BOTTOM		3

typedef struct edgeRef
{
	int tile;
	edgeTypeMask_t typeMask;
} edgeRef_t;

typedef struct tile
{
	int tx, ty;
	edgeRef_t edges[4];
} tile_t;

tile_t tiles[] =
{
	{.tx = 50,  .ty = 0,    .edges = { 3, LEFT | INV, 5, LEFT,   1, NONE,		  2, NONE}},
	{.tx = 100, .ty = 0,    .edges = { 0, NONE,       5, BOTTOM, 4, RIGHT | INV,  2, RIGHT}},
	{.tx = 50,  .ty = 50,   .edges = { 3, TOP,        0, NONE,   1, BOTTOM,	      4, NONE}},
	{.tx = 0,   .ty = 100,  .edges = { 0, LEFT | INV, 2, LEFT,   4, NONE,		  5, NONE}},
	{.tx = 50,  .ty = 100,  .edges = { 3, NONE,       2, NONE,   1, RIGHT | INV,  5, RIGHT}},
	{.tx = 0,   .ty = 150,  .edges = { 0, TOP,        3, NONE,   4, BOTTOM,	      1, TOP}}
};

void updateMovementDirection(int newDir, int* incX, int* incY);
char getWorldTile(int x, int y);
int wrapCoordinates(int* px, int* py, int* pdir);
void loadWorld(void);

char world[WIDTH*HEIGHT];
worldInfo_t infoW[HEIGHT];
worldInfo_t infoH[WIDTH];
int tile = 0;
int posX;
int posY;
int dir = -1;

main()
{
	int i, step, steps, movementLen;
	int newX, newY, tmpDir, tmpTile, incX, incY;

	loadWorld();

	movementLen = strlen(path);
	for (i = 0; i < movementLen; ++i)
	{
		steps = atoi(&path[i]);
		while (path[i] >= '0' && path[i] <= '9') {
			++i;
		}

		updateMovementDirection(dir, &incX, &incY);

		for (step = 0; step < steps; ++step)
		{
			newX = posX + incX;
			newY = posY + incY;

			tmpDir = dir;
			tmpTile = wrapCoordinates(&newX, &newY, &tmpDir);

			if (getWorldTile(newX, newY) == '#') {
				break;
			}

			posX = newX;
			posY = newY;
#if DAY == 2
			tile = tmpTile;
			if (tmpDir != dir) {
				updateMovementDirection(tmpDir, &incX, &incY);
			}
#endif
		}

		if (i < movementLen)
		{
			if (path[i] == 'R') {
				dir = (dir + 1) % 4;
			}
			else {
				dir = (dir + 3) % 4;
			}
		}
	}

	printf("The final password is %d\n", (posY+1) * 1000 + (posX+1) * 4 + dir);

	return 0;
}

void updateMovementDirection(int newDir, int* incX, int* incY)
{
	dir = newDir;
	*incX = *incY = 0;
	if (dir == R) { *incX = 1; }
	else if (dir == D) { *incY = 1; }
	else if (dir == L) { *incX = -1; }
	else if (dir == U) { *incY = -1; }
}

char getWorldTile(int x, int y)
{
	return world[y * WIDTH + x];
}

#if DAY == 1
int wrapCoordinates(int* px, int* py, int* pdir)
{
	int x = *px;
	int y = *py;
	int dir = *pdir;

	if (dir == R || dir == L)
	{
		if (x >= infoW[y].width) {
			*px = infoW[y].offset;
		}
		else if (x < infoW[y].offset) {
			*px = infoW[y].width - 1;
		}
	}

	if (dir == U || dir == D)
	{
		if (y >= infoH[x].width) {
			*py = infoH[x].offset;
		}
		else if (y < infoH[x].offset) {
			*py = infoH[x].width - 1;
		}
	}

	return 0;
}
#else

int wrapCoordinates(int* px, int* py, int* pdir)
{
	int x = *px;
	int y = *py;
	int dir = *pdir;
	const edgeRef_t* edge = NULL;
	int edgeType = -1;
	int newTile = tile;

	const int index[] =
	{
		EDGE_INVALID, EDGE_LEFT, EDGE_TOP, EDGE_INVALID, EDGE_RIGHT, EDGE_INVALID, EDGE_INVALID, EDGE_INVALID, EDGE_BOTTOM
	};

	const int transitionEntryDir[] =
	{
		R, D, L, U
	};

	if (dir == R || dir == L)
	{
		if (x >= (tiles[tile].tx + TILE_WIDTH))
		{
			edgeType = index[RIGHT];
		}
		else if (x < tiles[tile].tx)
		{
			edgeType = index[LEFT];
		}
	}

	if (dir == U || dir == D)
	{
		if (y >= (tiles[tile].ty + TILE_WIDTH))
		{
			edgeType = index[BOTTOM];
		}
		else if (y < tiles[tile].ty)
		{
			edgeType = index[TOP];
		}
	}

	if (edgeType != EDGE_INVALID)
	{
		edge = &tiles[tile].edges[edgeType];

		if ((edge->typeMask & EDGE_TYPE_MASK_EDGE_ONLY) != NONE)
		{
			x = x - tiles[tile].tx;
			y = y - tiles[tile].ty;

			if (edge->typeMask & INV)
			{
				x = TILE_WIDTH - 1 - x;
				y = TILE_WIDTH - 1 - y;
			}

			if (edgeType == EDGE_LEFT || edgeType == EDGE_RIGHT)
			{
				switch (edge->typeMask & EDGE_TYPE_MASK_EDGE_ONLY)
				{
				case LEFT:
					x = tiles[edge->tile].tx;
					y = tiles[edge->tile].ty + y;
					break;
				case RIGHT:
					x = tiles[edge->tile].tx + TILE_WIDTH - 1;
					y = tiles[edge->tile].ty + y;
					break;
				case TOP:
					x = tiles[edge->tile].tx + y;
					y = tiles[edge->tile].ty;
					break;
				case BOTTOM:
					x = tiles[edge->tile].tx + y;
					y = tiles[edge->tile].ty + TILE_WIDTH - 1;
					break;
				}
			}
			else
			{
				switch (edge->typeMask & EDGE_TYPE_MASK_EDGE_ONLY)
				{
				case LEFT:
					y = tiles[edge->tile].ty + x;
					x = tiles[edge->tile].tx;
					break;
				case RIGHT:
					y = tiles[edge->tile].ty + x;
					x = tiles[edge->tile].tx + TILE_WIDTH - 1;
					break;
				case TOP:
					x = tiles[edge->tile].tx + x;
					y = tiles[edge->tile].ty;
					break;
				case BOTTOM:
					x = tiles[edge->tile].tx + x;
					y = tiles[edge->tile].ty + TILE_WIDTH - 1;
					break;
				}
			}

			*px = x;
			*py = y;
			*pdir = transitionEntryDir[index[edge->typeMask & EDGE_TYPE_MASK_EDGE_ONLY]];
		}

		newTile = edge->tile;
	}
	return newTile;
}
#endif

void parseLine(const char* line, char* target, int* offset, int* width)
{
	while (*line)
	{
		if (*line == ' ')
			*offset = *offset + 1;
		*target++ = *line++;
		*width = *width + 1;
	}
}

void loadWorld(void)
{
	int x, y;

	memset(world, ' ', sizeof(world));

	for (x = 0; x < HEIGHT; ++x)
	{
		parseLine(data[x], &world[x*WIDTH], &infoW[x].offset, &infoW[x].width);
	}

	for (x = 0; x < WIDTH; ++x)
	{
		for (y = 0; ; ++y)
		{
			if (getWorldTile(x, y) != ' ') {
				break;
			}

			infoH[x].offset++;
			infoH[x].width++;
		}

		for (; y < HEIGHT; ++y)
		{
			if (getWorldTile(x, y) == ' ') {
				break;
			}
			infoH[x].width++;
		}
	}

	posX = infoW[0].offset;
	posY = 0;
	dir = R;
}