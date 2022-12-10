#include <stdio.h>
#include <string.h>

#include "day10.h"

#define DAY 2

#define GFX_WIDTH 40
#define GFX_HEIGHT 6
#define SPRITE_WIDTH 3

typedef struct cpu_t
{
  int reg;
  int cycle;
  char vmem[GFX_WIDTH*GFX_HEIGHT];
} cpu;

void tick(long* sum);
void vmemToScreen(void);

cpu g_cpu;

main()
{
  int i, value;
  long sum = 0;
  char command[8];

  g_cpu.reg = 1;
  g_cpu.cycle = 1;

  clrscr();

  for (i = 0; i < (sizeof(data)/sizeof(data[0])); ++i)
  {
    sscanf(data[i], "%s %d", command, &value);

    if (!strcmp(command, "noop"))
    {
      tick(&sum);
    }
    else if (!strcmp(command, "addx"))
    {
      tick(&sum);
      tick(&sum);
      g_cpu.reg += value;
    }
  }

#if DAY == 1
  printf("The sum of the six signal strengths is %ld\n", sum);
#else
  vmemToScreen();
#endif

  return 0;
}

void tick(long* sum)
{
#if DAY == 2
  int pos = (g_cpu.cycle - 1) % GFX_WIDTH;
  int scanLine = (g_cpu.cycle - 1) / GFX_WIDTH;
  int spritePos = g_cpu.reg - 1;

  if (pos >= spritePos && pos < spritePos + SPRITE_WIDTH)
  {
    g_cpu.vmem[scanLine*GFX_WIDTH+pos] = '#';
  }
  else
  {
    g_cpu.vmem[scanLine*GFX_WIDTH+pos] = '.';
  }
#else
  if (g_cpu.cycle == 20 || ((g_cpu.cycle - 20) % 40) == 0)
  {
    *sum += g_cpu.cycle * g_cpu.reg;
  }
#endif

  g_cpu.cycle++;
}

void vmemToScreen()
{
  int x, y;

  for (y = 0; y < GFX_HEIGHT; ++y)
  {
    for (x = 0; x < GFX_WIDTH; ++x)
    {
      printf("%c", g_cpu.vmem[y*GFX_WIDTH+x]);
    }
    printf("\n");
  }
}