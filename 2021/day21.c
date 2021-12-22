#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define PART 2

#if 1
#define START_PLAYER1 8
#define START_PLAYER2 9
#else
#define START_PLAYER1 4
#define START_PLAYER2 8
#endif

#if PART == 1
#define MAX_SCORE 1000
#else
#define MAX_SCORE 21
#endif

#define INITIAL_HASH 5381
#define MAX_BUCKETS 64
#define MAX_CACHE_ENTRIES 900

typedef struct pair128_t
{
	__int64 a;
	__int64 b;
} pair128;

typedef struct cacheEntry_t
{
	struct pair128_t value;
	unsigned long key;
} cacheEntry;

cacheEntry buckets[MAX_BUCKETS][MAX_CACHE_ENTRIES];
int bucketCounts[MAX_BUCKETS];

const int pdf[][2] =
{
	{3, 1}, {4, 3}, {5, 6}, {6, 7}, {7, 6}, {8, 3}, {9, 1}
};

unsigned long hash(unsigned long hash, int value)
{
	hash = ((hash << 5) + hash) + ((value >> 24) & 0xff);
	hash = ((hash << 5) + hash) + ((value >> 16) & 0xff);
	hash = ((hash << 5) + hash) + ((value >> 8) & 0xff);
	hash = ((hash << 5) + hash) + ((value >> 0) & 0xff);
	return hash;
}

unsigned long hash4(int value1, int value2, int value3, int value4)
{
	unsigned long h = hash(INITIAL_HASH, value1);
	h = hash(h, value2);
	h = hash(h, value3);
	h = hash(h, value4);
	return h;
}

int solve1(int playerPos1, int playerPos2)
{
	int prevSum = 0;
	int playerScore[2] = { 0, 0 };
	int playerPos[2] = { playerPos2, playerPos1 };
	int draws = 1;

	for (; playerScore[0] < MAX_SCORE && playerScore[1] < MAX_SCORE; ++draws)
	{
		int sum = ((draws * 3 * (draws * 3 + 1)) / 2) - prevSum;
		prevSum += sum;
		int index = draws & 1;
		playerPos[index] = (playerPos[index] + sum) % 10;
		playerScore[index] += playerPos[index] + 1;
	}

	int looserScore = (playerScore[0] < playerScore[1]) ? playerScore[0] : playerScore[1];

	return looserScore * (draws * 3 - 3);
}

pair128 solve2r(int playerPos1, int playerPos2, int playerScore1, int playerScore2)
{
	pair128 result = { 0, 0 };

	if (playerScore1 >= 21) {
		result.a = 1;
	}
	else if (playerScore2 >= 21) {
		result.b = 1;
	}
	else
	{
		unsigned long hash = hash4(playerPos1, playerPos2, playerScore1, playerScore2);
		int bucketIndex = hash & 0x3f;
		cacheEntry* bucket = buckets[bucketIndex];
		int numHashEntries = bucketCounts[bucketIndex];
		for (int i = 0; i < numHashEntries; ++i)
		{
			if (bucket[i].key == hash)
				return bucket[i].value;
		}

		for (int i = 0; i < _countof(pdf); ++i)
		{
			int newPos = (playerPos1 + pdf[i][0]) % 10;
			int newScore = playerScore1 + newPos + 1;
			pair128 value = solve2r(playerPos2, newPos, playerScore2, newScore);
			result.a += value.b * pdf[i][1];
			result.b += value.a * pdf[i][1];
		}

		cacheEntry entry = { .key = hash, .value = result };
		bucket[numHashEntries] = entry;
		assert(bucketCounts[bucketIndex] < MAX_CACHE_ENTRIES && "bucket running out of memory...");
		bucketCounts[bucketIndex]++;
	}

	return result;
}

__int64 solve2()
{
	pair128 value = solve2r(START_PLAYER1 - 1, START_PLAYER2 - 1, 0, 0);
	return value.a > value.b ? value.a : value.b;
}

int main()
{
#if PART == 1
	printf("%d\n", solve1(START_PLAYER1 - 1, START_PLAYER2 - 1));
#else
	printf("%I64d\n", solve2());
#endif
}