#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define PART 2

typedef struct vec2_t
{
    int x, y;
} vec2;

#if 0
vec2 min = { 20, -10 };
vec2 max = { 30, -5 };
#else
vec2 min = { 195, -93 };
vec2 max = { 238, -67 };
#endif

bool isOutOfRange(int velX, int velY, int x, int y)
{
    return ((velX > 0 && x > max.x) || (velX < 0 && x < min.x) || y < min.y);
}

bool isInside(int x, int y)
{
    return (x >= min.x && x <= max.x && y >= min.y && y <= max.y);
}

bool simulate(int velX, int velY, int* result)
{
    int posX = 0;
    int posY = 0;
    int maxY = *result;

    while (!isOutOfRange(velX, velY, posX, posY))
    {
        posX = posX + velX;
        posY = posY + velY;
        velY -= 1;
        velX -= ((velX > 0) - (velX < 0)); // velX > 0 ? -1 : velX < 0 ? 1 : 0
        maxY = maxY ^ ((maxY ^ posY) & -(maxY < posY)); // max(maxY, posY)

        if (isInside(posX, posY))
        {
            *result = maxY;
            return true;
        }
    }

    return false;
}

int main()
{
    int yRange = abs(min.y);
    int maxY = 0;
    int hits = 0;

    for (int y = -yRange; y <= yRange; ++y)
    {
        for (int x = 0; x <= max.x; ++x)
        {
            if (simulate(x, y, &maxY))
                ++hits;
        }
    }

#if PART == 1
    printf("%d\n", maxY);
#else
    printf("%d\n", hits);
#endif
}