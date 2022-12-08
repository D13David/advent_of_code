#include <stdio.h>

#include "day8.h"

#define WIDTH 99
#define HEIGHT 99
#define DAY 2

typedef enum { false, true } bool;

bool visibleFromDirectionX(int index, int x, int y, int* dist);
bool visibleFromDirectionY(int index, int x, int y, int* dist);

main()
{
  int i, x, y, sum;
  int dist[4];
  long scoreMap[WIDTH*HEIGHT], maxScore;

  for (i = 0, sum = 0; i < WIDTH*HEIGHT; ++i)
  {
    x = i % WIDTH;
    y = i / WIDTH;

    if (visibleFromDirectionX(i, x, y, &dist[0]) | visibleFromDirectionY(i, x, y, &dist[2]))
    {
      sum++;
    }

    scoreMap[i] = (long)dist[0] * dist[1] * dist[2] * dist[3];
  }

#if DAY == 1
  printf("%d trees are visible from outside the grid\n", sum);
#else
  for (i = 0, maxScore = -1; i < WIDTH*HEIGHT; ++i)
  {
    if (scoreMap[i] > maxScore) {
      maxScore = scoreMap[i];
    }
  }

  printf("The highest scenic score is %ld\n", maxScore);
#endif

  return 0;
}

bool visibleFromDirectionX(int index, int x, int y, int* dist)
{
  int i, dist1, dist2;
  bool visibleLeft = true, visibleRight = true;

  for (i = x-1, dist1 = 0; i >= 0 && visibleLeft; --i)
  {
    visibleLeft = (data[y*WIDTH+i] < data[index]);
    ++dist1;
  }

  for (i = x+1, dist2 = 0; i < WIDTH && visibleRight; ++i)
  {
    visibleRight = (data[y*WIDTH+i] < data[index]);
    ++dist2;
  }

  dist[0] = dist1;
  dist[1] = dist2;

  return visibleLeft || visibleRight;
}

bool visibleFromDirectionY(int index, int x, int y, int* dist)
{
  int i, dist1, dist2;
  bool visibleTop = true, visibleBottom = true;

  for (i = y-1, dist1 = 0; i >= 0 && visibleTop; --i)
  {
    visibleTop = (data[i*WIDTH+x] < data[index]);
    ++dist1;
  }

  for (i = y+1, dist2 = 0; i < HEIGHT && visibleBottom; ++i)
  {
    visibleBottom = (data[i*WIDTH+x] < data[index]);
    ++dist2;
  }

  dist[0] = dist1;
  dist[1] = dist2;

  return visibleTop || visibleBottom;
}