#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "day24.h"

#define DAY 2

#define STARTX	1
#define STARTY	0
#define TARGETX	150
#define TARGETY 21

#define INITIAL_HASH 5381
#define MAX_STATES (64*1024)
#define MAX_HASH_ITEMS (4*1024)

#define HEIGHT	22
#define WIDTH	152
#define LCM		300 // H * GCD(H,W) / W
#define BOARD_SIZE HEIGHT * WIDTH

char boards[BOARD_SIZE * LCM];

typedef struct state
{
	int x, y, t;
} state_t;

void precompute();
int solve(int startX, int startY, int startT, int targetX, int targetY);

main()
{
	int pathLength;

	precompute();

	pathLength = solve(STARTX, STARTY, 0, TARGETX, TARGETY);
#if DAY == 2
	pathLength = solve(TARGETX, TARGETY, pathLength, STARTX, STARTY);
	pathLength = solve(STARTX, STARTY, pathLength, TARGETX, TARGETY);
#endif
	printf("%d\n", pathLength);

	return 0;
}

unsigned long hash(unsigned long hash, int value)
{
	hash = ((hash << 5) + hash) + ((value >> 24) & 0xff);
	hash = ((hash << 5) + hash) + ((value >> 16) & 0xff);
	hash = ((hash << 5) + hash) + ((value >> 8) & 0xff);
	hash = ((hash << 5) + hash) + ((value >> 0) & 0xff);
	return hash;
}

unsigned long hash3(int value1, int value2, int value3)
{
	unsigned long h = hash(INITIAL_HASH, value1);
	h = hash(h, value2);
	h = hash(h, value3);
	return h;
}

void precompute()
{
	int i, x, y, xn, yn;
	char* p;

	for (i = 0; i < LCM; ++i)
	{
		p = &boards[BOARD_SIZE * i];
		memcpy(p, emptyBoard, BOARD_SIZE);

		for (y = 0; y < HEIGHT; ++y)
		{
			for (x = 0; x < WIDTH; ++x)
			{
				if (data[y][x] == '.' || data[y][x] == '#') {
					continue;
				}

				xn = x - 1;
				yn = y - 1;
				switch (data[y][x])
				{
				case '<': xn = (xn + LCM - i) % (WIDTH-2); break;
				case '>': xn = (xn + i) % (WIDTH-2); break;
				case 'v': yn = (yn + i) % (HEIGHT-2); break;
				case '^': yn = (yn + LCM - i) % (HEIGHT-2); break;
				}
				p[(yn+1) * WIDTH + (xn+1)] = data[y][x];
			}
		}
	}
}

state_t queue[MAX_STATES];
int tail, front;
unsigned long cache[64][MAX_HASH_ITEMS];
int cacheItems[64];

int empty()
{
	return front == tail;
}
void enqueue(state_t state)
{
	queue[tail % MAX_STATES] = state;
	++tail;
}
state_t dequeue()
{
	state_t state = queue[front];
	front = (front + 1) % MAX_STATES;
	return state;
}

int solve(int startX, int startY, int startT, int targetX, int targetY)
{
	int i;
	state_t state, next;
	unsigned long hashValue;
	const char* board;

	const int nb[] =
	{
		1, 0,
		0, 1,
		0, 0,
		-1, 0,
		0, -1
	};

	tail = front = 0;
	memset(cacheItems, 0, sizeof(cacheItems));

	state.x = startX;
	state.y = startY;
	state.t = startT;
	enqueue(state);

	while (!empty())
	{
		state = dequeue();

		if (state.x == targetX && state.y == targetY) {
			return state.t;
		}

		hashValue = hash3(state.x, state.y, state.t%LCM);

		for (i = 0; i < cacheItems[hashValue & 63]; ++i)
		{
			if (cache[hashValue & 63][i] == hashValue) {
				break;
			}
		}

		if (i < cacheItems[hashValue & 63]) {
			continue;
		}
		cache[hashValue & 63][cacheItems[hashValue & 63]++] = hashValue;
		assert(cacheItems[hashValue & 63] < MAX_HASH_ITEMS);

		for (i = 0; i < 5; ++i)
		{
			next.x = state.x + nb[i * 2 + 0];
			next.y = state.y + nb[i * 2 + 1];
			next.t = state.t + 1;

			if (next.x < 0 || next.x > WIDTH - 1) {
				continue;
			}

			if (next.y < 0 || next.y > HEIGHT - 1) {
				continue;
			}

			board = &boards[(next.t % LCM) * BOARD_SIZE];
			if (board[next.y * WIDTH + next.x] == '.') {
				enqueue(next);
			}
		}
	}

	return -1;
}