#include <stdio.h>
#include <alloc.h>
#include <assert.h>

#include "day12.h"

#define DAY 2

#define WIDTH 159
#define HEIGHT 41
#define NUM_ELEMENTS WIDTH*HEIGHT
#define MAX_NODES 65

typedef enum { false, true } bool;

typedef struct node_t
{
  int index;
  unsigned dist;
  struct node_t* next;
} node;

int adjacency[NUM_ELEMENTS][4];
void* mem;
struct node_t* freeList;
unsigned far* distance;

void initialize();
unsigned findShortestPath(int start, int end);
node* allocNode(unsigned dist, int index);
bool empty(struct node_t** head);
int top(struct node_t** head);
void pop(struct node_t** head);
void push(struct node_t** head, unsigned dist, int index);
void MM_init();
node* MM_alloc();
void MM_free(struct node_t* node);

main()
{
  int i, end;
  int startIndices[2048];
  unsigned numStartIndices, currPath, bestPath;

  MM_init();

  numStartIndices = 0;
  bestPath = 0x7fff;
  distance = (unsigned far*)farmalloc(NUM_ELEMENTS * sizeof(unsigned));
  assert(distance != NULL);

  for (i = 0; i < NUM_ELEMENTS; ++i)
  {
    if (data[i] == 'S')
    {
#if DAY == 1
      startIndices[numStartIndices++] = i;
#endif
      data[i] = 'a';
    }
    else if (data[i] == 'E')
    {
      end = i;
      data[i] = 'z';
    }
#if DAY == 2
    if (data[i] == 'a') {
      startIndices[numStartIndices++] = i;
    }
#endif
  }

  initialize();

  for (i = 0; i < numStartIndices; ++i)
  {
    currPath = findShortestPath(startIndices[i], end);
    if (currPath < bestPath) {
      bestPath = currPath;
    }
  }
  printf("The best path is %d steps long\n", bestPath);

  free(mem);
  farfree(distance);

  return 0;
}

int dist(int x1, int y1, int x2, int y2)
{
  return data[y1*WIDTH+x1] - data[y2*WIDTH+x2];
}

void initialize()
{
  int i, j, x, y, count;

  for (i = 0; i < NUM_ELEMENTS; ++i)
  {
    x = i % WIDTH;
    y = i / WIDTH;

    for (j = 0; j < 4; ++j) {
      adjacency[i][j] = -1;
    }

    count = 0;
    if (x > 0 && dist(x, y, x-1, y) >= -1) {
      adjacency[i][count++] = y * WIDTH + (x - 1);;
    }
    if (x < WIDTH - 1 && dist(x, y, x+1, y) >= -1) {
      adjacency[i][count++] = y * WIDTH + (x + 1);
    }
    if (y > 0 && dist(x, y, x, y-1) >= -1) {
      adjacency[i][count++] = (y - 1) * WIDTH + x;
    }
    if (y < HEIGHT - 1 && dist(x, y, x, y+1) >= -1) {
      adjacency[i][count++] = (y + 1) * WIDTH + x;
    }
  }
}

unsigned findShortestPath(int start, int end)
{
  int i, index, nb, cost;
  struct node_t* queue;

  for (i = 0; i < NUM_ELEMENTS; ++i)
    distance[i] = 0xffff;

  queue = NULL;
  push(&queue, 0, start);
  distance[start] = 0;

  while (empty(&queue) == false)
  {
    index = top(&queue);
    pop(&queue);

    for (i = 0; i < 4; ++i)
    {
      nb = adjacency[index][i];
      if (nb == -1) {
        continue;
      }

      cost = 1 + distance[index];
      if (distance[nb] > cost)
      {
        distance[nb] = cost;
        push(&queue, cost, nb);
      }
    }
  }

  return distance[end];
}

node* allocNode(unsigned dist, int index)
{
  struct node_t* node = MM_alloc();
  node->index = index;
  node->dist = dist;
  node->next = NULL;
  return node;
}

bool empty(struct node_t** head)
{
  return *head == NULL;
}

int top(struct node_t** head)
{
  return (*head)->index;
}

void pop(struct node_t** head)
{
  struct node_t* node = *head;
  *head = (*head)->next;
  MM_free(node);
}

void push(struct node_t** head, unsigned dist, int index)
{
  struct node_t* curr, *new = allocNode(dist, index);

  if (*head == NULL) {
    *head = new;
    return;
  }

  if ((*head)->dist > dist)
  {
    new->next = *head;
    *head = new;
  }
  else
  {
    curr = *head;

    while (curr->next && curr->next->dist < dist) {
      curr = curr->next;
    }

    new->next = curr->next;
    curr->next = new;
  }
}

void MM_init()
{
  int i;
  struct node_t* node;

  mem = malloc(MAX_NODES * sizeof(struct node_t));
  assert(mem != NULL);
  node = (struct node_t*)mem;
  for (i = 0; i < MAX_NODES; ++i) {
    MM_free(node++);
  }
}

node* MM_alloc()
{
  struct node_t* node;

  if (!freeList) {
    printf("out of memory...\n");
    exit(0);
  }

  node = freeList;
  freeList = *((struct node_t**)freeList);
  return node;
}

void MM_free(struct node_t* node)
{
  *(struct node_t**)node = freeList;
  freeList = node;
}