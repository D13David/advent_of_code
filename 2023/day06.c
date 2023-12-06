#include "day06.h"

#include <stdio.h>

#define PART 2

int isValid(unsigned __int64 ms, unsigned __int64 time, unsigned __int64 dist)
{
    return ms * (time - ms) > dist;
}

main()
{
    int result = 1;

#if PART == 1
    for (int i = 0; i < sizeof(time) / sizeof(time[0]); ++i)
    {
        int count = 0;
        for (int t = 0; t < time[i]; ++t)
        {
            if (isValid(t, time[i], dist[i])) {
                ++count;
            }
        }
        result *= count;
    }
#else
    unsigned __int64 min = 0, max = time1 / 2;
    while (max >= min)
    {
        unsigned __int64 mid = (min + max) / 2;
        if (isValid(mid, time1, dist1)) {
            max = mid - 1;
        }
        else {
            min = mid + 1;
        }
    }

    result = time1 - 2 * (min)+1;
#endif

    printf("%d\n", result);
}