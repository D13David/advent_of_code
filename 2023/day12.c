#include "day12.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define PART        2

#define MAX_GROUPS  32

__int64 cache[4 * 1024];

__int64 count(int springIndex, int groupIndex, const char* springs, int springsLength, const int* groups, int groupsLength)
{
    // all groups are distributed, so we have a match
    if (groupIndex >= groupsLength) {
        return 1;
    }

    const unsigned short key = ((unsigned short)springIndex << 5) | (unsigned short)groupIndex;
    assert(key < sizeof(cache) / sizeof(cache[0]));
    if (cache[key] != -1) {
        return cache[key];
    }

    __int64 result = 0;
    const int currentGroupLength = groups[groupIndex];
    
    for (int i = springIndex, atEnd = 0; !atEnd && i <= springsLength - currentGroupLength; ++i)
    {
        int currentGroupValid = 1;

        // check if there is a functioning spring within the current potential group range. if there is
        // the current position is _not_ a currentGroupValid group
        for (int j = 0; j < currentGroupLength; ++j)
        {
            if (springs[i + j] == '.') {
                currentGroupValid = 0;
            }
        }

        // if group is surrounded left or right with a broken spring, the total group length is too long
        // and therefore no currentGroupValid group
        if ((i > 0 && springs[i - 1] == '#') ||
            (i + currentGroupLength < springsLength && springs[i + currentGroupLength] == '#')) {
            currentGroupValid = 0;
        }

        // if this group is the last potential group but there are still broken springs left in the spring
        // list we don't have a match
        if (groupIndex == groupsLength - 1)
        {
            for (int j = i + currentGroupLength + 1; currentGroupValid && j < springsLength; ++j)
            {
                if (springs[j] == '#') {
                    currentGroupValid = 0;
                }
            }
        }

        if (currentGroupValid) 
        {
            result += count(i + currentGroupLength + 1, groupIndex + 1,
                            springs, springsLength, groups, groupsLength);
        }

        atEnd = (springs[i] == '#');
    }

    assert(cache[key] == -1 || cache[key] == result);
    cache[key] = result;

    return result;
}

main()
{
    unsigned __int64 sum = 0;

    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i)
    {
        char springs[512];
        int groups[MAX_GROUPS];

        strncpy(springs, data[i], 512);
        
        // split string
        char* numbers = strstr(springs, " ") + 1;
        numbers[-1] = '\0';
        int springsLength = numbers - springs - 1;

        int groupsLength = 0;
        const char* token = strtok(numbers, ",");
        while (token)
        {
            assert(groupsLength < MAX_GROUPS);
            groups[groupsLength++] = atoi(token);
            token = strtok(NULL, ",");
        }

#if PART == 2
        assert(groupsLength * 5 < MAX_GROUPS);
        for (int j = 0; j < groupsLength; ++j)
        {
            groups[1 * groupsLength + j] = groups[j];
            groups[2 * groupsLength + j] = groups[j];
            groups[3 * groupsLength + j] = groups[j];
            groups[4 * groupsLength + j] = groups[j];
        }
        groupsLength = groupsLength * 5;
#endif

#if PART == 2
        springs[springsLength++] = '?';
        for (int j = 0; j < springsLength; ++j)
        {
            springs[1 * springsLength + j] = springs[j];
            springs[2 * springsLength + j] = springs[j];
            springs[3 * springsLength + j] = springs[j];
            springs[4 * springsLength + j] = springs[j];
        }
        springsLength = springsLength * 5 - 1;
        springs[springsLength] = '\0';
#endif

        memset(cache, 0xffffffff, sizeof(cache));

        sum += count(0, 0, springs, springsLength, groups, groupsLength);
    }

    printf("%lld\n", sum);
}