typedef enum types_t
{
  X = 0, // ROCK
  Y,     // PAPER
  Z,     // SCISSORS
  A = 0, // ROCK
  B,     // PAPER
  C      // SCISSORS
} types;

#include "day2.h"

#define DAY 2

main()
{
  int i, score = 0;
  int valuePlayer, valueElf, valueWin;
  long totalScore = 0;

  for (i = 0; i < (sizeof(data)/sizeof(data[0])); i += 2)
  {
    valueElf = (int)data[i];
    valuePlayer = (int)data[i+1];

#if DAY == 2
    if (valuePlayer == 0)
    {
      valuePlayer = (valueElf - 1 + 3) % 3;
    }
    else if (valuePlayer == 1)
    {
      valuePlayer = valueElf;
    }
    else if (valuePlayer == 2)
    {
      valuePlayer = (valueElf + 1) % 3;
    }
#endif

    valueWin = (valuePlayer - 1 + 3) % 3;
    score = valuePlayer + 1; // selected shape
    if (valuePlayer == valueElf) // draw
      score += 3;
    else if (valueElf == valueWin) // win
      score += 6;

    totalScore += score;
  }

  printf("total score of %ld\n", totalScore);

  return 0;
}