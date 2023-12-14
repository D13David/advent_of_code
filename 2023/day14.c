#include "day14.h"

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define PART        2

#define MAP_WIDTH   100
#define MAP_HEIGHT  100

#define CYCLES      1000000000

#define MAX_STATES  250

#define SWAP(a, b) do { \
    int tmp = a;        \
    a = b;              \
    b = tmp;            \
} while (0)

typedef struct state_s
{
    unsigned int key;
    char data[MAP_WIDTH][MAP_HEIGHT];
} state_t;

static unsigned int crc32(unsigned int crc, const void* buf, size_t size)
{
    const unsigned char* p = buf;

    while (size--) {
        crc = crc32Lut[(crc ^ *p++) & 0xff] ^ (crc >> 8);
    }

    return crc;
}

unsigned int hashMapState()
{
    unsigned int hash = crc32(0, data[0], MAP_WIDTH);
    for (int i = 1; i < MAP_HEIGHT; ++i) {
        hash = crc32(hash, data[i], MAP_WIDTH);
    }
    return hash;
}

void printMap()
{
    printf("%d\n", hashMapState());
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x) 
        {
            putch(data[y][x]);
        }
        putch('\n');
    }
    putch('\n');
}

void tiltNorth()
{
    for (int x = 0; x < MAP_WIDTH; ++x)
    {
        int floorHeight = 0;

        for (int y = 0; y < MAP_HEIGHT; ++y)
        {
            if (data[y][x] == 'O') 
            {
                SWAP(data[floorHeight][x], data[y][x]);
                floorHeight = floorHeight + 1;
            } 
            
            if (data[y][x] == '#') {
                floorHeight = y + 1;
            }
        }
    }
}

void tiltSouth()
{
    for (int x = 0; x < MAP_WIDTH; ++x)
    {
        int floorHeight = MAP_HEIGHT - 1;

        for (int y = MAP_HEIGHT - 1; y >= 0; --y)
        {
            if (data[y][x] == 'O')
            {
                SWAP(data[floorHeight][x], data[y][x]);
                floorHeight = floorHeight - 1;
            }

            if (data[y][x] == '#') {
                floorHeight = y - 1;
            }
        }
    }
}

void tiltWest()
{
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        int floorHeight = 0;
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            if (data[y][x] == 'O')
            {
                SWAP(data[y][floorHeight], data[y][x]);
                floorHeight = floorHeight + 1;
            }

            if (data[y][x] == '#') {
                floorHeight = x + 1;
            }
        }
    }
}

void tiltEast()
{
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        int floorHeight = MAP_WIDTH - 1;
        for (int x = MAP_WIDTH - 1; x >= 0; --x)
        {
            if (data[y][x] == 'O')
            {
                SWAP(data[y][floorHeight], data[y][x]);
                floorHeight = floorHeight - 1;
            }

            if (data[y][x] == '#') {
                floorHeight = x - 1;
            }
        }
    }
}

void tiltCycle()
{
    tiltNorth();
    tiltWest();
    tiltSouth();
    tiltEast();
}

main()
{
#if PART == 1
    tiltNorth();
#else
    state_t* states = (state_t*)malloc(sizeof(state_t) * MAX_STATES);

    for (int i = 0; i < MAX_STATES; ++i)
    {
        tiltCycle();

        int key = hashMapState();
        int state = -1;

        for (int j = 0; state == -1 && j < i; ++j)
        {
            if (states[j].key == key) {
                state = j;
            }
        }

        if (state != -1)
        {
            int index = (CYCLES - 1 - state) % (i - state) + state;
            memcpy(data, states[index].data, sizeof(data));
            break;
        }

        states[i].key = key;
        memcpy(states[i].data, data, sizeof(data));
    }

    free(states);
#endif

    int sum = 0;
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            if (data[y][x] == 'O') {
                sum += MAP_HEIGHT - y;
            }
        }
    }

    printf("%d\n", sum);
}