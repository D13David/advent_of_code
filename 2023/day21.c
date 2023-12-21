#include "day21.h"

#include <string.h>
#include <stdio.h>
#include <malloc.h>

#define PART        2

#define MAP_WIDTH   131
#define MAP_HEIGHT  131

char* maps[2];

int countPositions(int startX, int startY, int count)
{
    int mapIndex = 0;

    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            char c = data[y][x];
            if (c == 'S') {
                c = '.';
            }
            maps[0][y * MAP_WIDTH + x] = c;
            maps[1][y * MAP_WIDTH + x] = '.';
        }
    }

    maps[mapIndex][startY * MAP_WIDTH + startX] = 'O';

    for (int i = 0; i < count; ++i)
    {
        int targetIndex = (mapIndex + 1) % 2;

        for (int y = 0; y < MAP_HEIGHT; ++y)
        {
            for (int x = 0; x < MAP_WIDTH; ++x)
            {
                if (maps[mapIndex][y * MAP_WIDTH + x] == 'O')
                {
                    if (x < MAP_WIDTH - 1 && data[y][x + 1] != '#') maps[targetIndex][y * MAP_WIDTH + (x + 1)] = 'O';
                    if (x > 0 && data[y][x - 1] != '#') maps[targetIndex][y * MAP_WIDTH + (x - 1)] = 'O';
                    if (y < MAP_HEIGHT - 1 && data[y + 1][x] != '#') maps[targetIndex][(y + 1) * MAP_WIDTH + x] = 'O';
                    if (y > 0 && data[y - 1][x] != '#') maps[targetIndex][(y - 1) * MAP_WIDTH + x] = 'O';
                }
            }
        }

        mapIndex = targetIndex;
    }

    int sum = 0;
    for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; ++i)
    {
        if (maps[mapIndex][i] == 'O') ++sum;
    }

    return sum;
}

main()
{
    maps[0] = (char*)malloc(MAP_WIDTH * MAP_HEIGHT * sizeof(char));
    maps[1] = (char*)malloc(MAP_WIDTH * MAP_HEIGHT * sizeof(char));

#if PART == 1
    printf("%d\n", countPositions(MAP_WIDTH / 2, MAP_HEIGHT / 2, 64));
#else
    unsigned long long result = 0;
    const int numTilesHorizontal = (26501365 / MAP_WIDTH) - 1;

    unsigned long long numOddTiles = numTilesHorizontal / 2 * 2 + 1;
    numOddTiles *= numOddTiles;

    unsigned long long numEvenTiles = (numTilesHorizontal + 1) / 2 * 2;
    numEvenTiles *= numEvenTiles;

    // fully enclosed tiles
    int oddPoints = countPositions(MAP_WIDTH / 2, MAP_HEIGHT / 2, MAP_WIDTH * 2 + 1);
    int evenPoints = countPositions(MAP_WIDTH / 2, MAP_HEIGHT / 2, MAP_WIDTH * 2);

    result += numOddTiles * oddPoints + 
              numEvenTiles * evenPoints;

    // partially intersected corner tiles
    int tiles[4];
    tiles[0] = countPositions(MAP_WIDTH - 1, MAP_HEIGHT / 2, MAP_WIDTH - 1);
    tiles[1] = countPositions(MAP_WIDTH / 2, 0, MAP_WIDTH - 1);
    tiles[2] = countPositions(0, MAP_HEIGHT / 2, MAP_WIDTH - 1);
    tiles[3] = countPositions(MAP_WIDTH / 2, MAP_HEIGHT - 1, MAP_WIDTH - 1);

    for (int i = 0; i < 4; ++i) {
        result += tiles[i];
    }

    // partially intersected tiles
    tiles[0] = countPositions(MAP_WIDTH - 1, 0, MAP_WIDTH / 2 - 1);
    tiles[1] = countPositions(MAP_WIDTH - 1, MAP_HEIGHT -1, MAP_WIDTH / 2 - 1);
    tiles[2] = countPositions(0, 0, MAP_WIDTH / 2 - 1);
    tiles[3] = countPositions(0, MAP_HEIGHT - 1, MAP_WIDTH / 2 - 1);

    for (int i = 0; i < 4; ++i) {
        result += (unsigned long long)tiles[i] * (numTilesHorizontal + 1);
    }

    tiles[0] = countPositions(MAP_WIDTH - 1, 0, MAP_WIDTH * 3 / 2 - 1);
    tiles[1] = countPositions(MAP_WIDTH - 1, MAP_HEIGHT - 1, MAP_WIDTH * 3 / 2 - 1);
    tiles[2] = countPositions(0, 0, MAP_WIDTH * 3 / 2 - 1);
    tiles[3] = countPositions(0, MAP_HEIGHT - 1, MAP_WIDTH * 3 / 2 - 1);

    for (int i = 0; i < 4; ++i) {
        result += (unsigned long long)tiles[i] * numTilesHorizontal;
    }

    printf("%lld\n", result);
#endif
}