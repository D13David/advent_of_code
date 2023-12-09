#include "day09.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define PART        2

#define MAX_HISTORY 128

main()
{
    char buffer[512];
    int history[MAX_HISTORY];
    int sum = 0;

    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i)
    {
        strcpy(buffer, data[i]);

        int numValues = 0;
        const char* token = strtok(buffer, " ");
        for (; token; ++numValues)
        {
            assert(numValues < MAX_HISTORY);
            history[numValues] = atoi(token);
            token = strtok(NULL, " ");
        }

        int right = numValues - 1;
        int left = numValues;
        for (int allZero = 0; !allZero; )
        {
#if PART == 2
            assert(left < MAX_HISTORY);
            history[left++] = history[0];
#endif
            allZero = 1;
            for (int j = 0; j < right; ++j)
            {
                history[j] = history[j + 1] - history[j];
                allZero &= history[j] == 0;
            }

            right = right - 1;
        }

#if PART == 1
        for (int j = right + 1; j < numValues; ++j) {
            history[j] = history[j] + history[j - 1];
        }
        sum += history[numValues - 1];
#else
        for (int j = left - 2; j >= numValues; --j) {
            history[j] = history[j] - history[j + 1];
        }
        sum += history[numValues];
#endif
    }
    printf("%d\n", sum);
}