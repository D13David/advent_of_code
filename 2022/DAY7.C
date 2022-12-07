#include <stdio.h>
#include <assert.h>

#include "day7.h"

#define DAY 2
#define DATA_SIZE (sizeof(data)/sizeof(data[0]))

#define MAX_DIR_NUM 		203
#define MAX_DEPTH 		16
#define TOTAL_FS_VOLUME 	70000000
#define MIN_FS_FREE_SPACE 	30000000

typedef struct dir_t
{
  int parent;
  unsigned long totalSize;
} dir;

unsigned long listDirectory(int* index);

main()
{
  int i, j, depth = 0;
  unsigned long freeSpace, result = 0;
  const char* cur;
  dir directories[MAX_DIR_NUM];
  int parentIndex[MAX_DEPTH], index = -1;

  clrscr();

  parentIndex[0] = -1;

  for (i = 0; i < DATA_SIZE; )
  {
    assert(data[i][0] == '$');

    cur = data[i] + 2;

    if (!strncmp(cur, "cd", 2))
    {
      if (cur[3] == '.' && cur[4] == '.')
      {
        --depth;
      }
      else
      {
        ++depth;
        parentIndex[depth] = ++index;
        assert(index < MAX_DIR_NUM);
        directories[index].parent = parentIndex[depth-1];
      }

      ++i;
    }
    else if (!strncmp(cur, "ls", 2))
    {
      directories[index].totalSize = listDirectory(&i);
      for (j = directories[index].parent; j != -1; j = directories[j].parent)
      {
        directories[j].totalSize += directories[index].totalSize;
      }
    }
  }

#if DAY == 1
  result = 0;
  for (i = 0; i <= index; ++i)
  {
    if (directories[i].totalSize < 100000) {
      result += directories[i].totalSize;
    }
  }
#else
  freeSpace = TOTAL_FS_VOLUME - directories[0].totalSize;

  for (i = 0, result = -1; i <= index; ++i)
  {
    if ((freeSpace + directories[i].totalSize) >= MIN_FS_FREE_SPACE)
    {
      if (directories[i].totalSize < result) {
        result = directories[i].totalSize;
      }
    }
  }
#endif

  printf("result %lld\n", result);

  return 0;
}

unsigned long listDirectory(int* index)
{
  const char* cur;
  int i = *index + 1;
  unsigned long fileSize, totalSize = 0;

  for (; i < DATA_SIZE && *cur != '$'; ++i)
  {
    cur = data[i];

    if (*cur >= '0' && *cur <= '9')
    {
      sscanf(cur, "%ld", &fileSize);
      totalSize += fileSize;
    }
  }

  if (*cur != '$') {
    *index = i;
  }
  else {
    *index = i-1;
  }

  return totalSize;
}