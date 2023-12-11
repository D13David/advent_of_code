#include "day11.h"

#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <assert.h>

#define PART                2

#define DATA_WIDTH          140
#define DATA_HEIGHT         140

#define MAX_GALAXIES        450

#if PART == 1
#define GALAXY_EXPANSION    2
#else
#define GALAXY_EXPANSION    1000000
#endif

int galaxyMeterX[DATA_WIDTH];
int galaxyMeterY[DATA_HEIGHT];

#define MIN(a,b)((a)<(b)?(a):(b))
#define MAX(a,b)((a)>(b)?(a):(b))

void measureUniverse()
{
    for (int y = 0; y < DATA_HEIGHT; ++y)
    {
        int emptySpace = 1;
        for (int x = 0; x < DATA_WIDTH; ++x)
        {
            emptySpace &= data[y][x] != '#';
        }
        galaxyMeterY[y] = emptySpace ? GALAXY_EXPANSION : 1;
    }

    for (int x = 0; x < DATA_WIDTH; ++x)
    {
        int emptySpace = 1;
        for (int y = 0; y < DATA_HEIGHT; ++y)
        {
            emptySpace &= data[y][x] != '#';
        }
        galaxyMeterX[x] = emptySpace ? GALAXY_EXPANSION : 1;
    }
}

main()
{
    measureUniverse();

    int galaxies[MAX_GALAXIES][2];
    int numGalaxies = 0;

    for (int y = 0; y < DATA_HEIGHT; ++y)
    {
        for (int x = 0; x < DATA_WIDTH; ++x)
        {
            if (data[y][x] == '#') 
            {
                assert(numGalaxies < MAX_GALAXIES);
                galaxies[numGalaxies][0] = x;
                galaxies[numGalaxies][1] = y;
                ++numGalaxies;
            }
        }
    }

    unsigned __int64 sum = 0;
    for (int i = 0; i < numGalaxies; ++i)
    {
        for (int j = i+1; j < numGalaxies; ++j)
        {
            int x1 = MIN(galaxies[i][0], galaxies[j][0]);
            int x2 = MAX(galaxies[i][0], galaxies[j][0]);
            int y1 = MIN(galaxies[i][1], galaxies[j][1]);
            int y2 = MAX(galaxies[i][1], galaxies[j][1]);
            
            int dist = 0;
            for (int x = x1; x < x2; ++x) {
                dist += galaxyMeterX[x];
            }
            for (int y = y1; y < y2; ++y) {
                dist += galaxyMeterY[y];
            }

            sum += dist;
        }
    }
    printf("%lld\n", sum);
}