#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "day17.h"

#define DAY 2

#define HEIGHT 8000
#define MAX_SIZE_STATE_HISTORY 5*1024

#if DAY == 1
#define ROUNDS 2022
#else
#define ROUNDS 1000000000000
#endif

typedef enum { false, true } bool;
typedef unsigned char byte;

typedef struct shapedef
{
	unsigned bits;
	byte shift : 3;
	byte height : 4;
} shapedef_t;

typedef struct state
{
	unsigned key;
	unsigned currentHeight;
	unsigned round;
} state_t;

shapedef_t shapes[] = 
{
	{ 0x03C00000, 1, 5 },
	{ 0x01070400, 2, 7 },
	{ 0x00810E00, 2, 7 },
	{ 0x02040810, 4, 8 },
	{ 0x03060000, 3, 6 }
};

int max(int a, int b);
char unpack(unsigned shape, int scanline);
bool collides(unsigned shapeBits, int posy);
void storeCurrentState(int jetIndex, int shapeIndex, int currentHeight, int round);
bool findCycle(int* diffHeight, int* diffRound);

char board[HEIGHT];
state_t stateHistory[MAX_SIZE_STATE_HISTORY];
int nbHistoryItems;

main()
{
	long long round, cycleHeight = 0, cycles;
	int j, height = 0, diffHeight, diffRound;
	int posy, nbJets, shapeIndex = 4, jetIndex;
	int shiftl, shiftr;
	shapedef_t shape;

	nbJets = strlen(data);
	jetIndex = nbJets - 1;

	board[HEIGHT-1] = 0xff;

	for (round = 0; round < ROUNDS; ++round)
	{
		shapeIndex = (shapeIndex + 1) % 5;
		shape = shapes[shapeIndex];
		shiftr = shape.shift, shiftl = 2;
		posy = HEIGHT - height - shape.height;

		while (true)
		{
			jetIndex = (jetIndex + 1) % nbJets;
			switch (data[jetIndex])
			{
			case '<':
				if (shiftl > 0 && !collides(shape.bits << 1, posy))
				{
					shiftl--, shiftr++;
					shape.bits <<= 1;
				}
				break;
			case '>':
				if (shiftr > 0 && !collides(shape.bits >> 1, posy))
				{
					shiftr--, shiftl++;
					shape.bits >>= 1;
				}
				break;
			}

			if (collides(shape.bits, posy + 1)) {
				break;
			}
			
			posy++;
		}

		for (j = 0; j < 4; ++j) {
			board[posy + j] |= unpack(shape.bits, j);
		}
		height = max(height, HEIGHT - posy - 1);

#if DAY == 2
		if (cycleHeight == 0)
		{
			storeCurrentState(jetIndex, shapeIndex, height, (int)round);

			if (findCycle(&diffHeight, &diffRound))
			{
				cycles = (ROUNDS - round) / diffRound;
				cycleHeight = cycles * diffHeight;
				round += cycles * diffRound;
			}
		}
#endif
	}

	printf("the tower height is %lld units\n", height + cycleHeight);

	return 0;
}

int max(int a, int b)
{
	if (a > b) return a;
	return b;
}

char unpack(unsigned shapeBits, int scanline)
{
	return (shapeBits >> (4 - scanline - 1) * 7) & 0x7f;
}

bool collides(unsigned shapeBits, int posy)
{
	int i;
	for (i = 0; i < 4; ++i)
	{
		if ((unpack(shapeBits, i) & board[posy+i]) != 0) {
			return true;
		}
	}
	return false;
}

void storeCurrentState(int jetIndex, int shapeIndex, int currentHeight, int round)
{
	assert(nbHistoryItems < MAX_SIZE_STATE_HISTORY);
	state_t* curr = &stateHistory[nbHistoryItems++];
	curr->key = (jetIndex << 4) | shapeIndex;
	curr->currentHeight = currentHeight;
	curr->round = round;
}

bool findCycle(int* diffHeight, int* diffRound)
{
	int i, idx;
	state_t* items[3];

	items[0] = &stateHistory[nbHistoryItems - 1];

	for (i = nbHistoryItems - 2, idx = 1; i >= 0 && idx < 3; --i)
	{
		if (stateHistory[i].key == items[idx-1]->key) {
			items[idx++] = &stateHistory[i];
		}
	}

	if (idx == 3)
	{
		*diffHeight = items[0]->currentHeight - items[1]->currentHeight;
		*diffRound = items[0]->round - items[1]->round;
		return true;
	}

	return false;
}