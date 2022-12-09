#include <stdio.h>
#include <math.h>
#include <assert.h>

typedef enum { L, R, U, D } Dir;

typedef struct
{
  int x;
  int y;
} Pos;

typedef struct
{
  Dir dir;
  int steps;
} Item;

#include "day9.h"

#define DAY 2
#define BUCKETS 8
#define BUCKET_SIZE 1024

#if DAY == 1
#define KNOTS 2
#else
#define KNOTS 10
#endif

Pos simulateRopeStep(int incX, int incY, Pos* rope);

main()
{
  int i, j, k;
  Pos rope[KNOTS], tail;
  int incX, incY, visits[BUCKETS], size, bucket;
  Pos visitBucket[BUCKETS][BUCKET_SIZE];
  Pos inc[4];

  inc[0].x = -1, inc[0].y = 0;
  inc[1].x = 1, inc[1].y = 0;
  inc[2].x = 0, inc[2].y = -1;
  inc[3].x = 0, inc[3].y = 1;

  memset(rope, 0, sizeof(rope));
  memset(visits, 0, sizeof(visits));

  for (i = 0; i < (sizeof(data)/sizeof(data[0])); ++i)
  {
    incX = inc[data[i].dir].x;
    incY = inc[data[i].dir].y;

    for (j = 0; j < data[i].steps; ++j)
    {
      tail = simulateRopeStep(incX, incY, rope);

      bucket = (tail.x+tail.y) & (BUCKETS-1);
      size = visits[bucket];
      for (k = 0; k < size; ++k)
      {
        if (visitBucket[bucket][k].x == tail.x && visitBucket[bucket][k].y == tail.y) {
          break;
        }
      }

      if (k >= size)
      {
        assert(size+1 < BUCKET_SIZE);
        visitBucket[bucket][size++] = tail;
        visits[bucket] = size;
      }
    }
  }

  for (i = 1; i < BUCKETS; ++i) {
    visits[0] += visits[i];
  }
  printf("%d position where visited at least once\n", visits[0]);

  return 0;
}

Pos simulateRopeStep(int incX, int incY, Pos* rope)
{
  int i, dx, dy, sx, sy;

  rope[0].x += incX;
  rope[0].y += incY;

  for (i = 1; i < KNOTS; ++i)
  {
    dx = rope[i-1].x - rope[i].x;
    dy = rope[i-1].y - rope[i].y;

    if (abs(dx) <= 1 && abs(dy) <= 1) {
      continue;
    }

    // convert to -1,0,1
    sx = (dx != 0) | -(int)((unsigned int)((int)dx) >> (sizeof(int) * 8 - 1));
    sy = (dy != 0) | -(int)((unsigned int)((int)dy) >> (sizeof(int) * 8 - 1));

    rope[i].x += sx;
    rope[i].y += sy;
  }

  return rope[KNOTS-1];
}