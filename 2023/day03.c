#include "day03.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define PART        2

#define WIDTH       140
#define HEIGHT      140
#define MAX_NUMBERS 8

#define MIN(a,b) ((a)<(b)?(a):b)
#define MAX(a,b) ((a)>(b)?(a):b)

typedef struct symbol_s
{
    int numbers[MAX_NUMBERS];
    int nbNumbers;
    char value;
} symbol_t;

symbol_t symbols[WIDTH*HEIGHT];

symbol_t* checkSurrounding(int start, int end, int y)
{
    int isValid = 0;

    int minX = MAX(0, start);
    int maxX = MIN(WIDTH - 1, end);
    int minY = MAX(0, y - 1);
    int maxY = MIN(HEIGHT - 1, y + 1);

    for (int j = minY; j <= maxY; ++j)
    {
        for (int i = minX; i <= maxX; ++i) 
        {
            isValid |= data[j][i] != '.' && (data[j][i] < '0' || data[j][i] > '9');

            if (isValid) 
            {
                symbol_t* symbol = &symbols[j*WIDTH+i];
                symbol->value = data[j][i];
                return symbol;
            }
        }
    }

    return NULL;
}

main()
{
    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            if (data[y][x] >= '0' && data[y][x] <= '9')
            {
                int value = atoi(&data[y][x]);
                assert(value < 1000);

                int end, start = x - 1;
                if (value < 10) end = start + 2;
                else if (value < 100) end = start + 3;
                else if (value < 1000) end = start + 4;

                symbol_t* symbol = checkSurrounding(start, end, y);
                if (symbol != NULL) 
                {
                    assert(symbol->nbNumbers < MAX_NUMBERS - 1);
                    symbol->numbers[symbol->nbNumbers++] = value;
                }

                x = end;
            }
        }
    }

    int sum = 0;

    for (int i = 0; i < WIDTH*HEIGHT; ++i)
    {
        if (symbols[i].value == '\0') {
            continue;
        }
#if PART == 1
        for (int idx = 0; idx < symbols[i].nbNumbers; ++idx) {
            sum += symbols[i].numbers[idx];
        }
#else
        if (symbols[i].value == '*' && symbols[i].nbNumbers == 2)
        {
            int gearRatio = symbols[i].numbers[0] * symbols[i].numbers[1];
            sum += gearRatio;
        }
#endif
    }
    printf("%d\n", sum);
}