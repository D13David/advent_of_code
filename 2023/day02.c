#include "day02.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_GAMES   100
#define MAX_SETS    6

#define PART        2

typedef struct cube_set_s
{
    int red, green, blue;
} cube_set_t;

cube_set_t games[MAX_GAMES][MAX_SETS];

#define MAX(a,b) (((a)>(b))?(a):(b))

void parseSet(char* set, int* red, int* green, int* blue)
{
    *red = *green = *blue = 0;

    char* token = strtok(set, " ,");
    while (token)
    {
        int value = atoi(token);
        token = strtok(NULL, " ,");
        if (token != NULL)
        {
            switch (token[0])
            {
            case 'r': *red = value; break;
            case 'g': *green = value; break;
            case 'b': *blue = value; break;
            }
        }
        token = strtok(NULL, " ,");
    }
}

main()
{
    int id;
    char buffer[256], set[100];

    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i)
    {
        int result = sscanf(data[i], "Game %d: %[^\n]", &id, buffer);
        assert(result == 2);

        --id;

        const char* ptr = buffer;
        for (int index = 0; *ptr != '\0'; ++index)
        {
            sscanf(ptr, "%99[^;\n]s", set);
            ptr += strlen(set);
            if (*ptr == ';') {
                ++ptr;
            }

            parseSet(set, &games[id][index].red, &games[id][index].green, &games[id][index].blue);
        }
    }

    int sum = 0;
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i)
    {
#if PART == 1
        int stillPossible = 1;
        for (int j = 0; j < MAX_SETS && stillPossible; ++j)
        {
            stillPossible &= (games[i][j].red <= 12 && games[i][j].green <= 13 && games[i][j].blue <= 14);
        }
        if (stillPossible) {
            sum += i + 1;
        }
#elif PART == 2
        int r, g, b;
        r = g = b = 0;
        for (int j = 0; j < MAX_SETS; ++j)
        {
            r = MAX(games[i][j].red, r);
            g = MAX(games[i][j].green, g);
            b = MAX(games[i][j].blue, b);
        }
        sum += r * g * b;
#endif
    }

    printf("%d\n", sum);

    return 0;
}