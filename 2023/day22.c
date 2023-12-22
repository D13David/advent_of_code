#include "day22.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#define PART                    2

#define MAX_BRICKS (sizeof(data)/sizeof(data[0]))

#define MAX_SUPPORTING_BRICKS  10

#define MAX_WIDTH              10
#define MAX_DEPTH              10

typedef struct brick_s
{
    int min[3];
    int max[3];
    int supportingBricks[MAX_SUPPORTING_BRICKS];
    int numSupportingBricks;
} brick_t;

brick_t bricks[MAX_BRICKS];
short brickIds[MAX_DEPTH][MAX_WIDTH];
short heightMap[MAX_DEPTH][MAX_WIDTH];

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

int cmp(const void* a, const void* b)
{
    return ((const brick_t*)a)->min[2] - ((const brick_t*)b)->min[2];
}

int canRemoveBrick(int brick)
{
    for (int i = 0; i < MAX_BRICKS; ++i)
    {
        if (brick == i) {
            continue;
        }

        for (int j = 0; j < bricks[i].numSupportingBricks; ++j)
        {
            if (bricks[i].supportingBricks[j] == brick && bricks[i].numSupportingBricks == 1) {
                return 0;
            }
        }
    }
    return 1;
}

void addSupportingBrick(int brick, int supportingBrick)
{
    for (int i = 0; i < bricks[brick].numSupportingBricks; ++i)
    {
        if (bricks[brick].supportingBricks[i] == supportingBrick) {
            return;
        }
    }

    assert(bricks[brick].numSupportingBricks < MAX_SUPPORTING_BRICKS);
    bricks[brick].supportingBricks[bricks[brick].numSupportingBricks++] = supportingBrick;
}

int getSupportedBricks(int brick, int* supportedBricks, int maxSize)
{
    int count = 0;
    for (int i = 0; i < MAX_BRICKS; ++i)
    {
        for (int j = 0; j < bricks[i].numSupportingBricks; ++j)
        {
            if (bricks[i].supportingBricks[j] == brick)
            {
                assert(count < maxSize);
                supportedBricks[count++] = i;
            }
        }
    }
    return count;
}

int countAllFallingForBrick(int brick) 
{
    int candidates[MAX_BRICKS], numBricks = 0;
    int removed[MAX_BRICKS], numRemoved = 0;

    int supportedBricks[MAX_SUPPORTING_BRICKS];
    int numSupportedBricks = getSupportedBricks(brick, supportedBricks, MAX_SUPPORTING_BRICKS);
    for (int i = 0; i < numSupportedBricks; ++i)
    {
        assert(numBricks < MAX_BRICKS);
        candidates[numBricks++] = supportedBricks[i];
    }

    removed[numRemoved++] = brick;

    int brickToRemoveIndex = -1;

    do
    {
        brickToRemoveIndex = -1;
        for (int i = 0; i < numBricks; ++i)
        {
            int sum = 0;
            for (int j = 0; j < bricks[candidates[i]].numSupportingBricks; ++j)
            {
                for (int k = 0; k < numRemoved; ++k) 
                {
                    if (removed[k] == bricks[candidates[i]].supportingBricks[j])
                    {
                        ++sum;
                        break;
                    }
                }
            }

            if (sum == bricks[candidates[i]].numSupportingBricks)
            {
                brickToRemoveIndex = candidates[i];
                candidates[i] = candidates[numBricks - 1];
                --numBricks;
                break;
            }
        }

        if (brickToRemoveIndex != -1)
        {
            assert(numRemoved < MAX_BRICKS);
            removed[numRemoved++] = brickToRemoveIndex;

            int numSupportedBricks = getSupportedBricks(brickToRemoveIndex, supportedBricks, MAX_SUPPORTING_BRICKS);
            for (int i = 0; i < numSupportedBricks; ++i)
            {
                int alreadyContains = 0;
                for (int j = 0; !alreadyContains && j < numBricks; ++j)
                {
                    if (candidates[j] == supportedBricks[i]) {
                        alreadyContains = 1;
                    }
                }
                if (!alreadyContains)
                {
                    assert(numBricks < MAX_BRICKS);
                    candidates[numBricks++] = supportedBricks[i];
                }
            }
        }
    } while (brickToRemoveIndex != -1);

    return numRemoved;
}

main()
{
    memset(brickIds, -1, sizeof(brickIds));
    memset(heightMap, 0, sizeof(heightMap));

    for (int i = 0; i < MAX_BRICKS; ++i)
    {
        int result = sscanf(data[i], "%d,%d,%d~%d,%d,%d", &bricks[i].min[0], &bricks[i].min[1], &bricks[i].min[2],
            &bricks[i].max[0], &bricks[i].max[1], &bricks[i].max[2]);
        assert(result == 6);
    }

    qsort(bricks, MAX_BRICKS, sizeof(brick_t), &cmp);

    for (int i = 0; i < MAX_BRICKS; ++i)
    {
        int minX = bricks[i].min[0]; int maxX = bricks[i].max[0];
        int minY = bricks[i].min[1]; int maxY = bricks[i].max[1];
        int minZ = bricks[i].min[2]; int maxZ = bricks[i].max[2];

        int diffX = maxX - minX;
        int diffY = maxY - minY;
        int diffZ = maxZ - minZ;

        assert(diffX >= 0);
        assert(diffY >= 0);
        assert(diffZ >= 0);

        if (diffX != 0)
        {
            assert(diffY == 0 && diffZ == 0);

            int offsetZ = 0;
            for (int x = minX; x <= maxX; ++x) {
                offsetZ = MAX(offsetZ, heightMap[minY][x] + 1);
            }

            for (int x = minX; x <= maxX; ++x) 
            {
                int brickBelow = brickIds[minY][x];
                if (brickBelow != -1 && abs(offsetZ - heightMap[minY][x]) < 2) {
                    addSupportingBrick(i, brickBelow);
                }

                brickIds[minY][x] = i;
                heightMap[minY][x] = offsetZ;
            }
        }
        else if (diffY != 0)
        {
            assert(diffX == 0 && diffZ == 0);

            int offsetZ = 0;
            for (int y = minY; y <= maxY; ++y) {
                offsetZ = MAX(offsetZ, heightMap[y][minX] + 1);
            }

            for (int y = minY; y <= maxY; ++y) 
            {
                int brickBelow = brickIds[y][minX];
                if (brickBelow != -1 && abs(offsetZ - heightMap[y][minX]) < 2) {
                    addSupportingBrick(i, brickBelow);
                }

                brickIds[y][minX] = i;
                heightMap[y][minX] = offsetZ;
            }
        }
        else
        {
            // also handles one-cube bricks
            assert(diffX == 0 && diffY == 0); 

            int offsetZ = minZ - (heightMap[minY][minX] + 1);

            int brickBelow = brickIds[minY][minX];
            if (brickBelow != -1) {
                addSupportingBrick(i, brickBelow);
            }

            heightMap[minY][minX] = maxZ - offsetZ;
            brickIds[minY][minX] = i;
        }
    }

    int sum = 0;
    for (int brick = 0; brick < MAX_BRICKS; ++brick)
    {
#if PART == 1
        if (canRemoveBrick(brick)) {
            sum++;
        }
#else
        sum += countAllFallingForBrick(brick) - 1;
#endif
    }

    printf("%d\n", sum);
}