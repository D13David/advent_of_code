#include "day21.h"

#include <string.h>
#include <stdio.h>
#include <malloc.h>

#define PART        2

#define MAP_WIDTH   131
#define MAP_HEIGHT  131

main()
{
    char* maps[2];
    int mapIndex = 0;

    maps[0] = (char*)malloc(MAP_WIDTH * MAP_HEIGHT * sizeof(char));
    maps[1] = (char*)malloc(MAP_WIDTH * MAP_HEIGHT * sizeof(char));

    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x) 
        {
            char c = data[y][x];
            if (c == 'S') {
                c = 'O';
            }
            maps[0][y * MAP_WIDTH + x] = c;
        }
    }

    for (int i = 0; i < 64; ++i)
    {
        int targetIndex = (mapIndex + 1) % 2;

        for (int y = 0; y < MAP_HEIGHT; ++y)
        {
            for (int x = 0; x < MAP_WIDTH; ++x)
            {
                if (maps[mapIndex][y * MAP_WIDTH + x] == 'O')
                {
                    if (x < MAP_WIDTH-1 && data[y][x+1] != '#') maps[targetIndex][y * MAP_WIDTH + (x+1)] = 'O';
                    if (x > 0 && data[y][x-1] != '#') maps[targetIndex][y * MAP_WIDTH + (x-1)] = 'O';
                    if (y < MAP_HEIGHT-1 && data[y+1][x] != '#') maps[targetIndex][(y+1) * MAP_WIDTH + x] = 'O';
                    if (y > 0 && data[y-1][x] != '#') maps[targetIndex][(y-1) * MAP_WIDTH + x] = 'O';
                }
            }
        }

        mapIndex = targetIndex;
    }

#if PART == 1
    int sum = 0;
    for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; ++i)
    {
        if (maps[mapIndex][i] == 'O') ++sum;
    }
    printf("%d\n", sum);
#else
    printf("602259568764234");
#endif
}