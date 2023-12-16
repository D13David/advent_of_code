#include "day16.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PART                2

#define MAP_WIDTH           110
#define MAP_HEIGHT          110

#define DIR_NORTH           0
#define DIR_EAST            1
#define DIR_SOUTH           2
#define DIR_WEST            3

#define MAX_LIGHT_TRACES    10000

#define MAX(a,b) ((a)>(b)?(a):(b))

typedef struct lightTrace_s
{
    int dir   : 4;
    int posX  : 8;
    int posY  : 8;
    struct lightTrace_s* prev;
    struct lightTrace_s* next;
} lightTrace_t;

lightTrace_t lightTracePool[MAX_LIGHT_TRACES];
lightTrace_t* freeList;

void MM_free(lightTrace_t*);

void MM_init()
{
    lightTrace_t* entry = lightTracePool;
    for (int i = 0; i < MAX_LIGHT_TRACES; ++i) {
        MM_free(entry++);
    }
}

lightTrace_t* MM_alloc()
{
    if (!freeList) {
        printf("out of memory...\n");
        exit(0);
    }

    lightTrace_t* entry = freeList;
    freeList = *((lightTrace_t**)freeList);
    return entry;
}

void MM_free(lightTrace_t* entry)
{
    *(lightTrace_t**)entry = freeList;
    freeList = entry;
}

lightTrace_t* allocLightTrace(int dir, int posX, int posY)
{
    lightTrace_t* lightTrace = MM_alloc();
    lightTrace->dir = dir;
    lightTrace->posX = posX;
    lightTrace->posY = posY;
    lightTrace->prev = NULL;
    lightTrace->next = NULL;
    return lightTrace;
}

void printMap(const int* energized)
{
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            if (energized[y * MAP_WIDTH + x] != 0) {
                putch('#');
            }
            else {
                putch('.');
            }
        }
        putch('\n');
    }
    putch('\n');
}

int traceMap(int startX, int startY, int startDir)
{
    int energized[MAP_HEIGHT * MAP_WIDTH];

    memset(energized, 0, MAP_WIDTH * MAP_HEIGHT * sizeof(int));

    lightTrace_t* lightTraceHead = allocLightTrace(startDir, startX, startY);

    while (lightTraceHead)
    {
        for (lightTrace_t* trace = lightTraceHead; trace; trace = trace->next)
        {
            switch (trace->dir)
            {
            case DIR_NORTH:
                trace->posY--;
                break;
            case DIR_EAST:
                trace->posX++;
                break;
            case DIR_SOUTH:
                trace->posY++;
                break;
            case DIR_WEST:
                trace->posX--;
                break;
            }

            const char fieldValue = data[trace->posY][trace->posX];

            // trace is traveling out of map bounds
            int killLightTrace = trace->posX < 0 || trace->posX >= MAP_WIDTH || trace->posY < 0 || trace->posY >= MAP_HEIGHT;

            // cell is energized my a trace from the current direction. meaning the trace either loops
            // or a new trace enters a loop
            killLightTrace |= fieldValue == '.' && (energized[trace->posY * MAP_WIDTH + trace->posX] & (1 << trace->dir));

            if (killLightTrace)
            {
                lightTrace_t* prev = trace->prev;
                lightTrace_t* next = trace->next;

                if (prev) {
                    prev->next = next;
                }
                if (next) {
                    next->prev = prev;
                }

                // if the trace was the head of the list we set a new head and restart the loop
                if (!prev) {
                    lightTraceHead = next;
                    break;
                }

                MM_free(trace);

                // continue with previous light trace
                trace = prev;
                continue;
            }

            energized[trace->posY * MAP_WIDTH + trace->posX] |= (1 << trace->dir);

            lightTrace_t* newLightTrace = NULL;
            if ((trace->dir == DIR_NORTH || trace->dir == DIR_SOUTH) && fieldValue == '-')
            {
                trace->dir = DIR_EAST;
                newLightTrace = allocLightTrace(DIR_WEST, trace->posX, trace->posY);
            }
            if ((trace->dir == DIR_EAST || trace->dir == DIR_WEST) && fieldValue == '|')
            {
                trace->dir = DIR_NORTH;
                newLightTrace = allocLightTrace(DIR_SOUTH, trace->posX, trace->posY);
            }

            if (newLightTrace)
            {
                lightTrace_t* prev = trace->prev;
                lightTrace_t* next = trace->next;

                newLightTrace->next = next;
                newLightTrace->prev = trace;
                trace->next = newLightTrace;

                if (next) {
                    next->prev = newLightTrace;
                }
            }

            if (fieldValue == '\\')
            {
                const int map[] = { DIR_WEST, DIR_SOUTH, DIR_EAST, DIR_NORTH };
                trace->dir = map[trace->dir];
            }
            if (fieldValue == '/')
            {
                const int map[] = { DIR_EAST, DIR_NORTH, DIR_WEST, DIR_SOUTH };
                trace->dir = map[trace->dir];
            }
        }
    }

    int sum = 0;
    for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; ++i) {
        sum += energized[i] != 0;
    }

    return sum;
}

main()
{
    MM_init();

    int sum = 0;
#if PART == 1
    sum = traceMap(-1, 0, DIR_EAST);
#else
    for (int x = 0; x < MAP_WIDTH; ++x) 
    {
        sum = MAX(sum, traceMap(x, -1, DIR_SOUTH));
        sum = MAX(sum, traceMap(x, MAP_HEIGHT, DIR_NORTH));
    }

    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        sum = MAX(sum, traceMap(-1, y, DIR_EAST));
        sum = MAX(sum, traceMap(MAP_WIDTH, y, DIR_WEST));
    }
#endif

    printf("%d\n", sum);
}