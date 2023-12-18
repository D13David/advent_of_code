#include "day17.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define PART            2

#define MAX_NODES       100000
#define MAX_BUCKETS     100
#define MAP_WIDTH       141
#define MAP_HEIGHT      141

#define DIR_LEFT        0
#define DIR_RIGHT       1
#define DIR_UP          2
#define DIR_DOWN        3

#if PART == 2
#define MIN_TRAVEL      4
#define MAX_TRAVEL      10
#else
#define MAX_TRAVEL      3
#endif

// node allocator =============================================================
typedef struct node_s
{
    int posX;
    int posY;
    unsigned int dist;
    unsigned int dir  : 4;
    unsigned int run  : 4;
    struct node_s* next;
} node_t;

node_t nodePool[MAX_NODES];
node_t* allocFreeList;

void MM_free(node_t* node);

void MM_init()
{
    node_t* node = (node_t*)nodePool;
    for (int i = 0; i < MAX_NODES; ++i) {
        MM_free(node++);
    }
}

node_t* MM_alloc()
{
    if (!allocFreeList) {
        printf("out of memory...\n");
        exit(0);
    }

    node_t* node = allocFreeList;
    allocFreeList = *((node_t**)allocFreeList);
    return node;
}

void MM_free(node_t* node)
{
    *(node_t**)node = allocFreeList;
    allocFreeList = node;
}

// priority queue =============================================================
node_t* allocNode(node_t value)
{
    node_t* node = MM_alloc();
    *node = value;
    return node;
}

int empty(node_t** head)
{
    return (*head) == NULL;
}

node_t top(node_t** head)
{
    /*int prev = -1;
    for (node_t* node = *head; node; node = node->next) {
        if (prev == -1) prev = node->dist;
        else
        {
            assert(prev <= node->dist);
        }
    }*/
    return **head;
}

void pop(node_t** head)
{
    node_t* node = *head;
    (*head) = (*head)->next;
    MM_free(node);
}

void push(node_t** head, node_t value)
{
    node_t* newNode = allocNode(value);

    if (*head == NULL)
    {
        (*head) = newNode;
        return;
    }

    if ((*head)->dist > value.dist)
    {
        newNode->next = *head;
        (*head) = newNode;
    }
    else
    {
        node_t* currentHead = *head;

        while (currentHead->next != NULL && currentHead->next->dist < value.dist) {
            currentHead = currentHead->next;
        }

        newNode->next = currentHead->next;
        currentHead->next = newNode;
    }
}

void pushNodeWithUpdatedCost(node_t** head, node_t node)
{
    if (node.posX < 0 || node.posX >= MAP_WIDTH || node.posY < 0 || node.posY >= MAP_HEIGHT) {
        return;
    }

    node.dist = node.dist + data[node.posY][node.posX] - '0';
    push(head, node);
}

unsigned int visitedNodes[MAP_WIDTH][MAP_HEIGHT][10][4];

main()
{
    MM_init();

    node_t* queue = NULL;
    push(&queue, (node_t) { 0, 0, 0, 1});

    while (!empty(&queue))
    {
        node_t node = top(&queue);
        pop(&queue);

        // node state already visited
        unsigned int* visited = &visitedNodes[node.posY][node.posX][node.run][node.dir];
        if (*visited != 0 && *visited <= node.dist) {
            continue;
        }

        visitedNodes[node.posY][node.posX][node.run][node.dir] = node.dist;

        // found target map tile, return dist
        if (
#if PART == 2
            node.run >= MIN_TRAVEL-1 &&
#endif
            (node.posX == MAP_WIDTH - 1 && node.posY == MAP_HEIGHT - 1)) 
        {
            printf("at end %d", node.dist);
            break;
        }

        if (
#if PART == 2
            node.run >= MIN_TRAVEL-1 &&
#endif
            (node.dir == DIR_LEFT || node.dir == DIR_RIGHT))
        {
            pushNodeWithUpdatedCost(&queue, (node_t) { node.posX, node.posY - 1, node.dist, DIR_UP, 0 });
            pushNodeWithUpdatedCost(&queue, (node_t) { node.posX, node.posY + 1, node.dist, DIR_DOWN, 0 });
        }

        if (
#if PART == 2
            node.run >= MIN_TRAVEL-1 &&
#endif
            (node.dir == DIR_UP || node.dir == DIR_DOWN))
        {
            pushNodeWithUpdatedCost(&queue, (node_t) { node.posX - 1, node.posY, node.dist, DIR_LEFT, 0 });
            pushNodeWithUpdatedCost(&queue, (node_t) { node.posX + 1, node.posY, node.dist, DIR_RIGHT, 0 });
        }

        if (node.run < MAX_TRAVEL-1)
        {
            int x = node.posX;
            int y = node.posY;

            switch (node.dir)
            {
            case DIR_LEFT:  x--; break;
            case DIR_RIGHT: x++; break;
            case DIR_UP:    y--; break;
            case DIR_DOWN:  y++; break;
            }

            pushNodeWithUpdatedCost(&queue, (node_t) { x, y, node.dist, node.dir, node.run + 1 });
        }
    }
}