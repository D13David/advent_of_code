#include "day01.h"

#include <stdio.h>
#include <string.h>

#define PART 2

#if PART == 2
const char* digitNames[] = {
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};
const int digitNameLength[] = {
    3, 3, 5, 4, 4, 3, 5, 5, 4
};
#endif

int getDigitAt(const char* line)
{
    if (*line >= '0' && *line <= '9') {
        return *line - '0';
    }

#if PART == 2
    for (int i = 0; i < 9; ++i) 
    {
        if (!strncmp(line, digitNames[i], digitNameLength[i])) {
            return i + 1;
        }
    }
#endif

    return -1;
}

int main()
{
    int sum = 0;

    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i)
    {
        const char* line = data[i];
        int digit, first, second;

        for (int j = 0; line[j] != 0; ++j)
        {
            if ((digit = getDigitAt(&line[j])) >= 0) 
            {
                first = digit;
                break;
            }
        }

        for (int j = (int)strlen(line) - 1; j >= 0; --j)
        {
            if ((digit = getDigitAt(&line[j])) >= 0) 
            {
                second = digit;
                break;
            }
        }

        sum += first * 10 + second;
    }

    printf("result %d\n", sum);
}