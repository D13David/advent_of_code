#include "day23.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

#define PART        2

#define MAP_WIDTH   141
#define MAP_HEIGHT  141

#define MAX_NODES   64
#define MAX_EDGES   128

#define START_X     1
#define START_Y     0
#define END_X       (MAP_WIDTH-2)
#define END_Y       (MAP_HEIGHT-1)

//#define TEST
#ifdef TEST
#define MAP_WIDTH   23
#define MAP_HEIGHT  23
#define data data1
#endif

typedef struct node_s
{
    int x;
    int y;
} node_t;

typedef struct edge_s
{
    int target;
    int steps;
} edge_t;

node_t nodes[MAX_NODES];
int numNodes;

edge_t edges[MAX_NODES][MAX_EDGES];
int numEdges[MAX_NODES];

char visited[MAP_HEIGHT][MAP_WIDTH];

#define COUNT_NEIGHBOR(x, y) \
    if ((x) >= 0 && (x) < MAP_WIDTH && (y) >= 0 && (y) < MAP_HEIGHT && data[(y)][(x)] != '#') {\
        neighbors++; \
    }

#define MAX(a,b) ((a)>(b)?(a):(b))

int listContainsNode(int posX, int posY, const node_t* nodes, int numNodes)
{
    for (int i = 0; i < numNodes; ++i)
    {
        if (nodes[i].x == posX && nodes[i].y == posY)
        {
            return i;
        }
    }
    return -1;
}

int getPossibleNeighborsAt(int posX, int posY, int* pX, int* pY)
{
    int count = 0;
    const char tileInMap = data[posY][posX];

#if PART == 1
    if (tileInMap == '.' || tileInMap == '<')
#endif
    {
        int x = posX - 1;
        int y = posY;
        if (x >= 0 && data[y][x] != '#') 
        {
            *pX++ = x;
            *pY++ = y;
            count++;
        }
    }

#if PART == 1
    if (tileInMap == '.' || tileInMap == '>')
#endif
    {
        int x = posX + 1;
        int y = posY;
        if (x < MAP_HEIGHT && data[y][x] != '#')
        {
            *pX++ = x;
            *pY++ = y;
            count++;
        }
    }

#if PART == 1
    if (tileInMap == '.' || tileInMap == '^')
#endif
    {
        int x = posX;
        int y = posY - 1;
        if (y >= 0 && data[y][x] != '#')
        {
            *pX++ = x;
            *pY++ = y;
            count++;
        };
    }

#if PART == 1
    if (tileInMap == '.' || tileInMap == 'v')
#endif
    {
        int x = posX;
        int y = posY + 1;
        if (y < MAP_HEIGHT && data[y][x] != '#')
        {
            *pX++ = x;
            *pY++ = y;
            count++;
        };
    }

    return count;
}

int findMaxPathLength(int nodeIndex)
{
    int posX = nodes[nodeIndex].x;
    int posY = nodes[nodeIndex].y;

    if (posX == END_X && posY == END_Y) {
        return 0;
    }

    visited[posY][posX] = 1;

    int result = -1;

    for (int i = 0; i < numEdges[nodeIndex]; ++i)
    {
        node_t target = nodes[edges[nodeIndex][i].target];
        if (!visited[target.y][target.x])
        {
            result = MAX(result, findMaxPathLength(edges[nodeIndex][i].target) + edges[nodeIndex][i].steps);
        }
    }

    visited[posY][posX] = 0;

    return result;
}

main()
{
    nodes[numNodes++] = (node_t){ .x = START_X, .y = START_Y };
    nodes[numNodes++] = (node_t){ .x = END_X, .y = END_Y };

    // reduce number of graph nodes to nodes to nodes that are not reachable by exactly
    // one path
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            if (data[y][x] == '#') {
                continue;
            }

            int neighbors = 0;
            COUNT_NEIGHBOR(x - 1, y);
            COUNT_NEIGHBOR(x + 1, y);
            COUNT_NEIGHBOR(x, y - 1);
            COUNT_NEIGHBOR(x, y + 1);
            if (neighbors > 2) 
            {
                assert(numNodes < MAX_NODES);
                nodes[numNodes++] = (node_t){ .x = x, .y = y };
            }
        }
    }

    // build graph from remaining nodes
    typedef struct
    {
        int posX, posY, steps;
    } stackItem_t;

    stackItem_t stack[MAX_NODES];
    int stackSize = 0;

    for (int i = 0; i < numNodes; ++i)
    {
        assert(stackSize < MAX_NODES);
        stack[stackSize++] = (stackItem_t){ .posX = nodes[i].x, .posY = nodes[i].y, .steps = 0};

        memset(visited, 0, sizeof(visited));
        visited[nodes[i].y][nodes[i].x] = 1;

        while (stackSize != 0)
        {
            stackItem_t item = stack[--stackSize];
            int targetIndex = -1;

            if (item.steps != 0 && (targetIndex = listContainsNode(item.posX, item.posY, nodes, numNodes)) != -1)
            {
                assert(numEdges[i] < MAX_EDGES);
                edges[i][numEdges[i]].target = targetIndex;
                edges[i][numEdges[i]].steps = item.steps;
                numEdges[i]++;
                continue;
            }

            int posX[4];
            int posY[4];
            int numPossibleNeighbors = getPossibleNeighborsAt(item.posX, item.posY, posX, posY);
            for (int j = 0; j < numPossibleNeighbors; ++j)
            {
                if (!visited[posY[j]][posX[j]])
                {
                    assert(stackSize < MAX_NODES);
                    stack[stackSize++] = (stackItem_t){ .posX = posX[j], .posY = posY[j], .steps = item.steps + 1};
                    visited[posY[j]][posX[j]] = 1;
                }
            }
        }
    }

    memset(visited, 0, sizeof(visited));

    printf("%d\n", findMaxPathLength(0));
}