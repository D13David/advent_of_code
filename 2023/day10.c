#include "day10.h"

#include <stdio.h>
#include <string.h>

#define PART            2

#define HEADING_NORTH   0
#define HEADING_EAST    1
#define HEADING_SOUTH   2
#define HEADING_WEST    3

#define MAP_WIDTH       (sizeof(data[0]))
#define MAP_HEIGHT      (sizeof(data)/MAP_WIDTH)

typedef struct player_s
{
    int posx;
    int posy;
    int heading;
} player_t;

void movePlayer(player_t* player)
{
#if PART == 2
    data[player->posy][player->posx] = '*';
#endif

    switch (player->heading)
    {
    case HEADING_NORTH:
        player->posy--;
        break;
    case HEADING_EAST:
        player->posx++;
        break;
    case HEADING_SOUTH:
        player->posy++;
        break;
    case HEADING_WEST:
        player->posx--;
        break;
    }

    int currentTile = data[player->posy][player->posx];
    switch (player->heading)
    {
    case HEADING_NORTH:
        if (currentTile == 'F') {
            player->heading = (player->heading + 1) % 4;
        }
        else if (currentTile == '7') {
            player->heading = (player->heading + 3) % 4;
        }
        break;
    case HEADING_EAST:
        if (currentTile == '7') {
            player->heading = (player->heading + 1) % 4;
        }
        else if (currentTile == 'J') {
            player->heading = (player->heading + 3) % 4;
        }
        break;
    case HEADING_SOUTH:
        if (currentTile == 'J') {
            player->heading = (player->heading + 1) % 4;
        }
        else if (currentTile == 'L') {
            player->heading = (player->heading + 3) % 4;
        }
        break;
    case HEADING_WEST:
        if (currentTile == 'L') {
            player->heading = (player->heading + 1) % 4;
        }
        else if (currentTile == 'F') {
            player->heading = (player->heading + 3) % 4;
        }
        break;
    }
}

main()
{
    player_t player;
    int steps = 0;
#if PART == 2
    int distance[MAP_HEIGHT][MAP_WIDTH];
    memset(distance, 0, sizeof(distance));
#endif

    for (int i = 0; i < MAP_HEIGHT * MAP_HEIGHT; ++i)
    {
        int x = i % MAP_WIDTH;
        int y = i / MAP_WIDTH;
        if (data[y][x] == 'S')
        {
            player.posx = x;
            player.posy = y;
            player.heading = HEADING_NORTH;
            break;
        }
    }

    int startX = player.posx;
    int startY = player.posy;

    // walk once a full round along the pipe 
    //  part 1: ... and measure the full path length
    //  part 2: ... and mark the loop edges in the map
    do
    {
#if PART == 2
        distance[player.posy][player.posx] = steps;
#endif
        movePlayer(&player);
        ++steps;
    } while (startX != player.posx || startY != player.posy);

#if PART == 1
    printf("%d\n", steps / 2);
#else
    int count = 0;
    for (int y = 0; y < MAP_HEIGHT - 1; ++y)
    {
        int winding = 0;
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            if (data[y][x] == '*' && data[y + 1][x] == '*')
            {
                // loop edge moves upwards
                if (distance[y + 1][x] == ((distance[y][x] + 1) % steps)) {
                    ++winding;
                }
                
                // loop edge moves downward
                if (((distance[y + 1][x] + 1) % steps) == distance[y][x]) {
                    --winding;
                }
            }
            if (data[y][x] != '*' && winding != 0) {
                ++count;
            }
        }
    }
    printf("%d\n", count);
#endif
}