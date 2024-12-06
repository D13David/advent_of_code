#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

//#define USE_TEST_DATA

#ifndef USE_TEST_DATA
extern const char* data;
#define MAP_WIDTH  130
#define MAP_HEIGHT 130
#else
const char* data = 
"....#....."
".........#"
".........."
"..#......."
".......#.."
".........."
".#..^....."
"........#."
"#........."
"......#...";
#define MAP_WIDTH  10
#define MAP_HEIGHT 10
#endif

#define PART 2

enum { DIR_NORTH, DIR_EAST, DIR_SOUTH, DIR_WEST, NUM_DIRECTIONS };

#define FLAG_VISITED_NORTH  0x01
#define FLAG_VISITED_EAST   0x02
#define FLAG_VISITED_SOUTH  0x04
#define FLAG_VISITED_WEST   0x08
#define FLAG_OBSTACLE       0x10

typedef struct guard_s
{
    int     PosX;
    int     PosY;
    uint8_t Dir;
} guard_t;

typedef struct fieldInfo_s
{
    guard_t PrecomputedGuardState[NUM_DIRECTIONS];
    uint8_t Flags;
} fieldInfo_t;

fieldInfo_t g_MapBase[MAP_WIDTH * MAP_HEIGHT];
fieldInfo_t g_Map[MAP_WIDTH * MAP_HEIGHT];

char g_TraceMap[MAP_WIDTH * MAP_HEIGHT];

#define TRACE(state, check, move) {                                                       \
        while (true) {                                                                    \
            int index = (state)->PosY * MAP_WIDTH + (state)->PosX;                        \
            if ((state)->check || (g_Map[index].Flags & FLAG_OBSTACLE)) { \
                break;                                                                    \
            }                                                                             \
            (state)->move;                                                                \
        }                                                                                 \
    }

static void traceEast(guard_t* playerState)
{
    if (playerState->PosY >= 0 && playerState->PosY < MAP_HEIGHT) {
        TRACE(playerState, PosX >= MAP_WIDTH, PosX++);
    }
}

static void traceSouth(guard_t* playerState)
{
    if (playerState->PosX >= 0 && playerState->PosX < MAP_WIDTH) {
        TRACE(playerState, PosY >= MAP_HEIGHT, PosY++);
    }
}

static void traceWest(guard_t* playerState)
{
    if (playerState->PosY >= 0 && playerState->PosY < MAP_HEIGHT) {
        TRACE(playerState, PosX < 0, PosX--);
    }
}

static void traceNorth(guard_t* playerState)
{
    if (playerState->PosX >= 0 && playerState->PosX < MAP_WIDTH) {
        TRACE(playerState, PosY < 0, PosY--);
    }
}

static void traceSteps(int posX, int posY, int targetX, int targetY, int dir)
{
    int dx = 0, dy = 0;

    switch (dir)
    {
    case DIR_NORTH: posY += 1; dx = 1; break;
    case DIR_EAST:  posX -= 1; dy = 1;  break;
    case DIR_SOUTH: posY -= 1; dx = -1;  break;
    case DIR_WEST:  posX += 1; dy = -1;  break;
    }

    while (posX != targetX || posY != targetY)
    {
        if (posX >= 0 && posX < MAP_WIDTH && posY >= 0 && posY < MAP_HEIGHT) {
            g_TraceMap[posY * MAP_WIDTH + posX] = 'X';
        }
        posX += dx;
        posY += dy;
    }
}

static void precomputeObstacleState(fieldInfo_t* map, int obstacleIndex)
{
    int x = obstacleIndex % MAP_WIDTH; int y = obstacleIndex / MAP_WIDTH;

    fieldInfo_t* field = &map[obstacleIndex];

    // new obstacle... mark it as such
    bool isObstacleAddedToBase = (field->Flags & FLAG_OBSTACLE) == 0;
    if (isObstacleAddedToBase) {
        field->Flags |= FLAG_OBSTACLE;
    }

    // ----
    guard_t guard = (guard_t){ .PosX = x, .PosY = y + 1, .Dir = DIR_EAST };
    traceEast(&guard);
    field->PrecomputedGuardState[DIR_NORTH] = guard;

    if (isObstacleAddedToBase && x < MAP_WIDTH - 1 && y < MAP_HEIGHT - 1) 
    {
        guard = (guard_t){ .PosX = x + 1, .PosY = y };
        traceEast(&guard);

        if (guard.PosX >= MAP_WIDTH) {
            guard.PosX = MAP_WIDTH - 1;
        }

        for (int i = x + 1; i <= guard.PosX; ++i) 
        {
            fieldInfo_t* otherField = &map[(y + 1) * MAP_WIDTH + i];
            if (otherField->Flags & FLAG_OBSTACLE) {
                otherField->PrecomputedGuardState[DIR_SOUTH] = (guard_t){ .PosX = x, .PosY = y, .Dir = DIR_WEST };
            }
        }   
    }

    // ----
    guard = (guard_t){ .PosX = x - 1, .PosY = y, .Dir = DIR_SOUTH };
    traceSouth(&guard);
    field->PrecomputedGuardState[DIR_EAST] = guard;

    if (isObstacleAddedToBase && y < MAP_WIDTH - 1 && x > 1) 
    {
        guard = (guard_t){ .PosX = x, .PosY = y + 1 };
        traceSouth(&guard);

        if (guard.PosY >= MAP_HEIGHT) {
            guard.PosY = MAP_HEIGHT - 1;
        }

        for (int i = y + 1; i <= guard.PosY; ++i)
        {
            fieldInfo_t* otherField = &map[i * MAP_WIDTH + x - 1];
            if (otherField->Flags & FLAG_OBSTACLE) {
                otherField->PrecomputedGuardState[DIR_WEST] = (guard_t){ .PosX = x, .PosY = y, .Dir = DIR_NORTH };
            }
        }
    }

    // ----
    guard = (guard_t){ .PosX = x, .PosY = y - 1, .Dir = DIR_WEST };
    traceWest(&guard);
    field->PrecomputedGuardState[DIR_SOUTH] = guard;

    if (isObstacleAddedToBase && x > 1 && y > 1) 
    {
        guard = (guard_t){ .PosX = x - 1, .PosY = y };
        traceWest(&guard);

        if (guard.PosX < 0) {
            guard.PosX = 0;
        }

        for (int i = x - 1; i >= guard.PosX; --i)
        {
            fieldInfo_t* otherField = &map[(y - 1) * MAP_WIDTH + i];
            if (otherField->Flags & FLAG_OBSTACLE) {
                otherField->PrecomputedGuardState[DIR_NORTH] = (guard_t){ .PosX = x, .PosY = y, .Dir = DIR_EAST };
            }
        }
    }

    // ----
    guard = (guard_t){ .PosX = x + 1, .PosY = y, .Dir = DIR_NORTH };
    traceNorth(&guard);
    field->PrecomputedGuardState[DIR_WEST] = guard;

    if (isObstacleAddedToBase && y > 1 && x < MAP_WIDTH - 1) 
    {
        guard = (guard_t){ .PosX = x, .PosY = y - 1 };
        traceNorth(&guard);

        if (guard.PosY < 0) {
            guard.PosY = 0;
        }

        for (int i = y - 1; i >= guard.PosY; --i)
        {
            fieldInfo_t* otherField = &map[i * MAP_WIDTH + x + 1];
            if (otherField->Flags & FLAG_OBSTACLE) {
                otherField->PrecomputedGuardState[DIR_EAST] = (guard_t){ .PosX = x, .PosY = y, .Dir = DIR_SOUTH };
            }
        }
    }
}

static void precomputeMapState()
{
    // first fill in all obstacles, so tracing will find them correctly
    for (int i = 0; i < MAP_HEIGHT * MAP_HEIGHT; ++i)
    {
        if (data[i] == '#') 
        {
            g_MapBase[i].Flags = FLAG_OBSTACLE;
            g_Map[i].Flags = FLAG_OBSTACLE;
        }
    }

    // then precompute obstacles field states
    for (int i = 0; i < MAP_HEIGHT*MAP_HEIGHT; ++i) {
        if (g_MapBase[i].Flags & FLAG_OBSTACLE) {
            precomputeObstacleState(g_MapBase, i);
        }
    }

    memcpy(g_Map, g_MapBase, sizeof(g_Map));
}

bool simulate(guard_t guard, bool fillTraceMap)
{
    bool loop = false;

    int posX = guard.PosX, posY = guard.PosY;

    // we trace the player state to the next obstacle as the actual starting point
    traceNorth(&guard);

    if (fillTraceMap) {
        traceSteps(posX - 1, posY, guard.PosX, guard.PosY, DIR_WEST);
    }

    while (true)
    {
        fieldInfo_t* field = &g_Map[guard.PosY * MAP_WIDTH + guard.PosX];
        int dir = guard.Dir;

        // player approached the obstacle from this direction already, so we found a loop
        if (field->Flags & (1 << dir)) {
            loop = true;
            break;
        }

        field->Flags |= (1 << dir);

        if (fillTraceMap) {
            traceSteps(guard.PosX, guard.PosY, field->PrecomputedGuardState[dir].PosX, field->PrecomputedGuardState[dir].PosY, dir);
        }

        guard = field->PrecomputedGuardState[dir];

        // guard is now outside of the map area.. so we can stop the simulation
        if (guard.PosX < 0 || guard.PosX >= MAP_WIDTH || guard.PosY < 0 || guard.PosY >= MAP_HEIGHT) {
            break;
        }
    }
    return loop;
}

int main()
{
    int startPosX = 0, startPosY = 0;
    for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; ++i)
    {
        if (data[i] == '^')
        {
            startPosX = i % MAP_WIDTH;
            startPosY = i / MAP_WIDTH;
            break;
        }
    }

    precomputeMapState();

    guard_t playerState = { .PosX = startPosX, .PosY = startPosY, .Dir = DIR_NORTH };
    simulate(playerState, true);

#if PART == 1
    int result = 0;
    for (int i = 0; i < MAP_HEIGHT * MAP_HEIGHT; ++i) {
        if (g_TraceMap[i] == 'X') {
            ++result;
        }
    }
    printf("%d\n", result);
#else
    int loops = 0;
    for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; ++i)
    {
        if (g_TraceMap[i] != 'X') {
            continue;
        }

        memcpy(g_Map, g_MapBase, sizeof(g_Map));
        precomputeObstacleState(g_Map, i);

        playerState = (guard_t){ .PosX = startPosX, .PosY = startPosY, .Dir = DIR_NORTH };
        if (simulate(playerState, false)) {
            loops++;
        }
    }

    printf("%d\n", loops);
#endif
}

#ifndef USE_TEST_DATA
const char* data =
"....#...................................#...............#.................#.......#...#..........................................."
".........................#.........#....................................#...........................#......##..............##...#."
".....................................................................#.........................................#..#..............."
".............#........#...............................................................................#......................#...."
"....#.#.................................#......................................#...#..#..........#....#.....#.............#......."
"....................#.......#..............#.......#.#.............................#......................................#......."
"..............................................................................................#......#....................#......."
".........#.#..#...............................#........#.#........................................................#..............#"
"....#...........#.......#.......#....#...#....#..........#..........#......#...#................#.........................#......."
".......#...........................................................................................#.................#...........#"
"..................#.#....#..............................#....................#.................#....#..........#..........#......."
"...#...............#...................................................#................#........................................."
".................#..#.#.............#.#...................................#......................#....#..........#................"
".#..................#........................#..........#...........................#.......#......................#.#............"
"......#...........................................#.....#.....#...........#...........................#..............#............"
".........#...............................#.............................#.#.......................................................#"
"...#.........#.#........................#...#..............................................#...#...............#...#..#..........."
"..............................#.....................................#................#..........................#.........##......"
"..........#...........#.....#......#......#..............................#.....#......................................#..........."
"..........................#....#.........................................................#..................#...#.........#......."
"......................................#...........#.........#...............................#.............#...............#......."
".......................#........#.#....#...#...#................................................................#......#.........."
"......................#...............#................#..#.#...........#...#.......................#.........#.........#..#......"
"....#.................#..........#............#....#..............................................................#.#............."
".........................................................................................................................#...##..."
".....................#.......#................................................##.............#........#........................#.."
"........................#..#.....#.#...............#.......#.................#.............................................#.#...."
"......................................................................................#..#.............................#.........."
"..#........................................................#..........................#..............#.#.....................#...."
"...#...................#............#...#.....#....#..................................#.......................#..................."
"...#...........#..............#............................................................#....#.....#.....................#....."
"........................#..............#...................#.....#..#............................................................."
".....#....................#....................##..........#..............#......#...............#..........#.....#..........##..."
"....#.......#..........................................................#....................................#.#..................#"
"#......#.#.................................#........................................................................#.........#..."
"...............................#......#......................#...................................................................."
"..............#..........................#....................................#..........#.............#.........................."
".....#........#....#.........................#..#.................#.#.................#..........................................."
".................#..................#.#................................#..#..................................#......#............."
"...........................#.......................................................#...................#............#............."
".....................#.........#..#..........................#..................................#........#........................"
"..#................................................#.#.................................#.#..........#.....#......................#"
"..........................................................................#..................................................#.#.."
"..................................#..........................................#......................#............................."
".......#...............#..............................................#......................................................#...."
"..........................................^....................#.................................................................."
".........#.........#.........................................................................................#......#....#........"
".........#.........#.............................................................................................................."
"........#....#......................#...............#...........#..................#...........................................##."
"......#............#...........#................................................................#.......#........................."
"#.............................#..............................................................#..............#....................."
"...................................#...........#...................................................#........#..........#.........."
"....#.....................................................................................................#...........#......#...."
"....................................................#....#...................................#...................................."
"............#........#............................#..........#.............................#.....#..#.#..........................."
"...........#.................................................................#.............#......................................"
"....#.........................................#.#.......#...............#...........................#............##..............."
"..................#..............#...#........................................................................#....#...........#.."
".....................#.....#...#.....#.............#..............#...#...................................#......................."
".#...#.....#.............................................#...........#....#......................................................."
".#.....#.............................#................#......................#........................#.........................#."
"......................#.........................................#.............................................#.................#."
"...#...#....................#.................................................................#............#....#.......#........."
"...........#......#...............................#.......#......#........#..........#...........................................#"
"......................#....#..............##...........................................................#..........#..............."
".#......#.....................................................................#..#....#.....................#....................."
"....##....#...#.........#.............................#.........#...................#.............#....#................#........."
"..................................................................#...............................#..............................."
"....#.................#.#........................................................................................................."
"........................#..........................#...........#...................................#.#.......#...................."
"...........#.....................................................................................#...............................#"
"...........................................#..................................#..................................................."
".....#.........#......#..........#.........#.................................................................................#...."
"....#.....................#....#..#.........................................................................#..#.................."
"........................##..#........................#...#.........#.................#......................#..#....#............."
".............#................#.......#........#............................................................#......#.............."
"#....#................................#.............#..........#........#.....#...#..........##.....................#............."
"......#...#......#..........................................................................................#....#..#.........#..."
"#.................#..............##....#........................#....#...........................................#..........#.#..."
"........................#.#..#........................................#.............................................##............"
"..........#.........#.........................................................................................##.................."
"....#....#...........#.................#......................#........................#...#....................................#."
".......#..................................#..................#...................#...............................#.....#.....#...."
"#................................#...........#................##...#............#................................................."
".............................#...#....................................#...................................#...#..........#...#...."
".#......#.........#...#.......#.................##....#..................................................#...#...................."
"...........#........................................................................................................#............."
"......................................#......#..........#.....#.....................#...................#.#.................#....."
".....................................#............#................................................................##............."
".......................................#....................#...........................................##..#....................."
"..........................#.................................................................................#....................#"
"...........................................................#............#.........#..#....#.#............#.....#.................."
"....#.....................................#...........................................#........#.....................#............"
".............#.............#................#..........................#......................#..........................#........"
".........#.................#......#............#....#.#.............................#.......##......................#.#.......#..."
"..............................................................................................................#..................."
"#...#...............................................#...................#........................#...............#................"
".......#...#.......#..#..#..#..........#.........................................................................................."
"......#.##....................#......#........#............#................#.............#...................#............#......"
".....#..#......#.......................#..............................#...............................#..........................."
".#.................................#......#..............................................#........................................"
"....#...........................#..#........#...............#..#.......................................#......##.#.........#......"
"..................................#..................#......................#.....................#.......#.....................#."
".........#....................#....#...............................................#...................................#.........."
".........................................................#...#...............##..#...............................................#"
".#..#.............#.............#....................................#....................#.....#..#..........................#..."
".................#.........................#..#........................................#.................................#........"
".....................#....#................................#......#..............................................................."
"...............#..........................#...........#.............................................................#.........#..."
"...........##.......#................#..............................#..........................#....##.....#...................#.."
"......................#........#........#.........#..................................................##..#........................"
"....#........................#......................#.#..................#....#..................#.....................#.........."
".................#......#...#...................................#...............#....#.........#............................#....."
"#.................#...............................#......#..#..............................................###...#.......#........"
"..........#...........#..........................................................................................................#"
".......................#......................................#.................#.......#........#................................"
"..#.......#..#.............................................................................................................#......"
"#.........#......#........................#.#..............................................#...................##................."
"...#....#.....................................#..................................................................................."
".....................#.....................................................................#........................#.....#......."
".....#..#...............................................................##......#.#......#..#.#.......#........................#.."
".......#..........#....................................#.........#.................#.................#.....................#......"
"..............##.................................................#................#.........#.#............#........#............#"
".....................#.............#....................#...#.................#.........#........#................................"
".............#...........................................#........................................................................"
".....#...#.............#..............#..............#..................................................................#......#.."
".....##...................................##.....#.....#..#.........#...............#..........#.....#............#.#...........#."
"....#..................#.........#....................#....................#...#....#..............##............#..............#."
"..................#..........#.#.....................................#....#..............#.......#.....#...............#......#..#"
"..............#.........#.............................................................................................#...........";
#endif