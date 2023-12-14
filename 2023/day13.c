#include "day13.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

#define PART        2

#if PART == 1
#define ERROR_TOLERANCE 0
#else
#define ERROR_TOLERANCE 1
#endif

#define DATA_SIZE    (sizeof(data) / sizeof(data[0]))

#define MAX_MAP_X   64
#define MAX_MAP_Y   64

#define MIN(a,b) ((a)<(b)?(a):(b))

int countBitsSet(int value) 
{
    value = value - ((value >> 1) & 0x55555555);
    value = (value & 0x33333333) + ((value >> 2) & 0x33333333);
    return ((value + (value >> 4) & 0xF0F0F0F) * 0x1010101) >> 24;
}

int findHorizonalReflectionAxis(int* map, int height, int width)
{
    for (int i = 0; i < height - 1; ++i)
    {
        int differenceFound = 0;
        for (int j = i, k = i+1; differenceFound == 0 && j >= 0 && k < height; --j, ++k)
        {
#if PART == 1
            differenceFound |= map[j] ^ map[k];
#else
            differenceFound += countBitsSet(map[j] ^ map[k]);
#endif
        }

        if (differenceFound == ERROR_TOLERANCE) {
            return i + 1;
        }
    }
    return -1;
}

int compareBits(int num, int index, int width)
{
    const int mask = (1 << index) - 1;
    int bits1 = (num >> index) & mask;
    int bits2 = num & mask;

    int bitErrorsInLine = 0;

    for (int i = index - 1, k = index; i >= 0 && k < width; --i, ++k)
    {
        if ((bits1 & 1) != ((bits2 >> i) & 1)) 
        {
            ++bitErrorsInLine;
        }
        bits1 >>= 1;
    }

    return bitErrorsInLine;
}

int findVerticalReflectionAxis(int* map, int height, int width)
{
    int errors[MAX_MAP_X];
    memset(errors, 0, sizeof(errors));

    for (int i = 0; i < height; ++i)
    {
        for (int j = 1; j < width; ++j) {
            errors[j - 1] += compareBits(map[i], j, width);
        }
    }

    for (int i = 0; i < width - 1; ++i)
    {
        if (errors[i] == ERROR_TOLERANCE) {
            return width - i - 1;
        }
    }
    return -1;
}

main()
{
    int map[MAX_MAP_Y];

    int mapHeight = 0,
        mapWidth = strlen(data[0]);

    memset(map, 0, sizeof(map));

    int total = 0;
    for (int i = 0; i < DATA_SIZE; ++i)
    {
        if (data[i] == "") 
        {
            int sum = 0;
            int verticalReflectionAxis = findVerticalReflectionAxis(map, mapHeight, mapWidth);
            if (verticalReflectionAxis != -1) {
                sum += verticalReflectionAxis;
            }
            int horizontalReflectionAxis = findHorizonalReflectionAxis(map, mapHeight, mapWidth);
            if (horizontalReflectionAxis != -1) {
                sum += 100 * horizontalReflectionAxis;
            }

            total += sum;

            memset(map, 0, sizeof(map));

            mapHeight = 0;
            if (i < DATA_SIZE - 1)
            {
                mapWidth = strlen(data[i + 1]);
                assert(mapWidth < 32);
            }
            continue;
        }

        assert(mapHeight < MAX_MAP_Y);
        for (int j = 0; j < mapWidth; ++j) 
        {
            map[mapHeight] = (map[mapHeight] << 1) | data[i][j] == '#';
        }
        ++mapHeight;
    }
    printf("%d\n", total);
}