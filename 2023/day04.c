#include "day04.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBERS     35
#define MY_NUMBERS      10

#define NUM_CARDS       (sizeof(data) / sizeof(data[0]))

#define PART            2

main()
{
    char line[256];
    int id;
    int numbers[MAX_NUMBERS];
    int numberOfCards[NUM_CARDS];

    for (int i = 0; i < NUM_CARDS; ++i) {
        numberOfCards[i] = 1;
    }

    int sum = 0;
    for (int i = 0; i < NUM_CARDS; ++i)
    {
        sscanf(data[i], "Card %d: %255[^\n]", &id, line);

        char* token = strtok(line, " |");
        for (int j = 0; token; ++j)
        {
            numbers[j] = atoi(token);
            token = strtok(NULL, " |");
        }

        int score = 1;
        for (int j = 0; j < MY_NUMBERS; ++j)
        {
            int number = numbers[j];
            for (int k = MY_NUMBERS; k < MAX_NUMBERS; ++k)
            {
                if (number == numbers[k])
                {
#if PART == 1
                    score *= 2;
#else
                    ++score;
#endif
                }
            }
        }
#if PART == 2
        for (int j = 1; j < score; ++j) {
            numberOfCards[i + j] = numberOfCards[i + j] + numberOfCards[i];
        }
#else
        sum += (score >> 1);
#endif
    }

#if PART == 2
    for (int i = 0; i < NUM_CARDS; ++i)
    {
        sum += numberOfCards[i];
    }
#endif

    printf("%d\n", sum);
}