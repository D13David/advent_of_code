#include "day18.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>

#define PART      2

#define SIZE_DATA (sizeof(data)/sizeof(data[0]))

typedef struct point_s
{
    unsigned __int64 x, y;
} point_t;

// 0 means R, 1 means D, 2 means L, and 3 means U

main()
{
    point_t points[SIZE_DATA+1];
    __int64 boundaryPoints = 0;

    points[0] = (point_t){ 0, 0 };

    for (int i = 0; i < SIZE_DATA; ++i)
    {
        char dir;
        int steps, color;
        int result = sscanf(data[i], "%c %d (#%6x)", &dir, &steps, &color);
        assert(result == 3);

#if PART == 2
        steps = color >> 4;
        dir = color & 3;
#else
        switch (dir)
        {
        case 'R': dir = 0; break;
        case 'D': dir = 1; break;
        case 'L': dir = 2; break;
        case 'U': dir = 3; break;
        }
#endif

        points[i + 1] = points[i];
        switch (dir)
        {
        case 0: points[i + 1].x += steps; break;
        case 1: points[i + 1].y += steps; break;
        case 2: points[i + 1].x -= steps; break;
        case 3: points[i + 1].y -= steps; break;
        }

        boundaryPoints += steps;
    }

    // calculate polygon area using https://en.wikipedia.org/wiki/Shoelace_formula
    __int64 laguneArea = 0;
    for (int i = 0; i < SIZE_DATA; ++i)
    {
        const int indexPrev = (i + SIZE_DATA - 1) % SIZE_DATA;
        const int indexNext = (i + 1) % SIZE_DATA;
        laguneArea = laguneArea + points[i].y * (points[indexNext].x - points[indexPrev].x);
    }

    if (laguneArea < 0) {
        laguneArea = laguneArea * -1;
    }
    laguneArea = laguneArea / 2;


    // calculate polygon inner points with https://en.wikipedia.org/wiki/Pick%27s_theorem
    // to cope with sample offsets with sample points being centered to half unit cubes
    unsigned __int64 innerArea = laguneArea - boundaryPoints / 2 + 1;

    printf("%lld\n", innerArea + boundaryPoints);
}