#include <stdlib.h>
#include <stdio.h>

#define PART 2

int data1[] =
{
	4,2,4,1,5,1,2,2,4,1,1,2,2,2,4,4,1,2,1,1,4,1,2,1,2,2,2,2,5,2,2,3,1,4,4,4,1,2,3,4,4,5,4,3,5,1,2,5,1,1,5,5,1,4,4,5,1,3,1,4,5,5,5,4,1,2,3,4,2,1,2,1,2,2,1,5,5,1,1,1,1,5,2,2,2,4,2,4,2,4,2,1,2,1,2,4,2,4,1,3,5,5,2,4,4,2,2,2,2,3,3,2,1,1,1,1,4,3,2,5,4,3,5,3,1,5,5,2,4,1,1,2,1,3,5,1,5,3,1,3,1,4,5,1,1,3,2,1,1,1,5,2,1,2,4,2,3,3,2,3,5,1,5,1,2,1,5,2,4,1,2,4,4,1,5,1,1,5,2,2,5,5,3,1,2,2,1,1,4,1,5,4,5,5,2,2,1,1,2,5,4,3,2,2,5,4,2,5,4,4,2,3,1,1,1,5,5,4,5,3,2,5,3,4,5,1,4,1,1,3,4,4,1,1,5,1,4,1,2,1,4,1,1,3,1,5,2,5,1,5,2,5,2,5,4,1,1,4,4,2,3,1,5,2,5,1,5,2,1,1,1,2,1,1,1,4,4,5,4,4,1,4,2,2,2,5,3,2,4,4,5,5,1,1,1,1,3,1,2,1
};

int data2[] =
{
	3,4,3,1,2
};

#define data data1

__int64 fishPerAge[9];

int main()
{
	for (int i = 0; i < _countof(data); ++i)
	{
		fishPerAge[data[i]]++;
	}

#if PART == 1
	const int DaysToSimulate = 80;
#else
	const int DaysToSimulate = 256;
#endif

	for (int i = 0; i < DaysToSimulate; ++i)
	{
		__int64 spawnFish = fishPerAge[0];

		for (int i = 1; i < _countof(fishPerAge); ++i)
		{
			fishPerAge[i - 1] = fishPerAge[i];
		}

		fishPerAge[6] += spawnFish;
		fishPerAge[8] = spawnFish;
	}

	__int64 fishTotal = 0;
	for (int i = 0; i < _countof(fishPerAge); ++i)
	{
		fishTotal += fishPerAge[i];
	}
	printf("%I64d\n", fishTotal);
}