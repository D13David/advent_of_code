#include "day05.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define PART        2

#define MAX_SEEDS   256
#define MAX_MAPS    7
#define MAX_RANGES  64

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

typedef struct range_s
{
    unsigned __int64 start;
    unsigned __int64 length;
} range_t;

typedef struct map_range_s
{
    unsigned __int64 source;
    unsigned __int64 target;
    unsigned __int64 length;
} map_range_t;

typedef struct map_s
{
    map_range_t ranges[MAX_RANGES];
    int numRanges;
} map_t;

map_t maps[MAX_MAPS];

void parseMaps()
{
    map_t* map = &maps[0];
    for (int i = 3; i < sizeof(data) / sizeof(data[0]); ++i)
    {
        if (data[i] == "")
        {
            ++map;
            i += 2;
        }

        assert(map->numRanges < MAX_RANGES);
        map_range_t* range = &map->ranges[map->numRanges++];
        int result = sscanf(data[i], "%lld %lld %lld", &range->target, &range->source, &range->length);
        assert(result == 3);
    }
}

int filter(const range_t* ranges, int numRanges, const map_t* map, range_t* result)
{
    range_t rangeStack[MAX_SEEDS];
    int rangeIndex = 0;
    int resultIndex = 0;

    for (int i = 0; i < numRanges; ++i) {
        assert(rangeIndex < MAX_SEEDS);
        rangeStack[rangeIndex++] = ranges[i];
    }

    while (rangeIndex > 0)
    {
        range_t range = rangeStack[--rangeIndex];

        int rangeInteractionFound = 0;

        for (int i = 0; i < map->numRanges; ++i)
        {
            /**
                (a) seed range does not overlap (any) source range
                (b) seed range overlaps
                    (1) intersection left
                    (2) intersection right
                    (3) seed range fully in source range
                    (4) intersection both (1) and (2)

                for (a) no mapping is found so seed range is returned as is. for overlapping cases (1), (2) and (4)
                the range needs to be split in two or three parts. the overlapping region is mapped to the target range
                and the remaining parts are handled like seperate seed ranges. in case of (3) the whole seed range is just 
                mapped to the target range

                (1)
                     |-----------------|            seed range
                |-----------|                       source rage
                     |++++++|----------|            seg overlap region

                (2)
                     |-----------------|
                              |-------------|
                     |--------|++++++++|

                (3)
                     |-----------------|
                |---------------------------|
                     |+++++++++++++++++|

                (4)
                     |-----------------|
                          |------|
                     |----|++++++|-----|
            */

            unsigned __int64 offset_start = MAX(range.start, map->ranges[i].source);
            unsigned __int64 offset_end = MIN(range.start + range.length, map->ranges[i].source + map->ranges[i].length);

            // check if ranges overlap
            if (offset_start < offset_end)
            {
                // map intersecting part of range to target
                assert(resultIndex < MAX_SEEDS);
                result[resultIndex].start = offset_start - map->ranges[i].source + map->ranges[i].target;
                result[resultIndex].length = (offset_end - map->ranges[i].source + map->ranges[i].target) - result[resultIndex].start;
                ++resultIndex;

                // split left part of current range
                if (offset_start > range.start)
                {
                    assert(rangeIndex < MAX_SEEDS);
                    rangeStack[rangeIndex].start = range.start;
                    rangeStack[rangeIndex].length = offset_start - range.start;
                    ++rangeIndex;
                }

                // split right part of current range
                if (range.start + range.length > offset_end)
                {
                    assert(rangeIndex < MAX_SEEDS);
                    rangeStack[rangeIndex].start = offset_end;
                    rangeStack[rangeIndex].length = range.start + range.length - offset_end;
                    ++rangeIndex;
                }

                // we found at least one mapping so at least parts of the range are mapped
                rangeInteractionFound = 1;
                break;
            }
        }

        if (!rangeInteractionFound)
        {
            assert(resultIndex < MAX_SEEDS);
            result[resultIndex].start = range.start;
            result[resultIndex].length = range.length;
            ++resultIndex;
        }
    }

    return resultIndex;
}

main()
{
    char line[256], *token;
    int numSeeds;
    range_t seeds[MAX_SEEDS];

    // parse seeds
    int result = sscanf(data[0], "seeds: %255[^\n]", line);
    assert(result == 1);

    numSeeds = 0;
    token = strtok(line, " ");
    while (token)
    {
        assert(numSeeds < MAX_SEEDS);
        seeds[numSeeds].start = _strtoui64(token, NULL, 10);
#if PART == 1
        seeds[numSeeds].length = 1;
#else
        token = strtok(NULL, " ");
        assert(token != NULL);
        seeds[numSeeds].length = _strtoui64(token, NULL, 10);
#endif
        ++numSeeds;
        token = strtok(NULL, " ");
    }

    parseMaps();

    for (int map = 0; map < MAX_MAPS; ++map) {
        numSeeds = filter(seeds, numSeeds, &maps[map], seeds);
    }

    unsigned __int64 minValue = seeds[0].start;
    for (int i = 1; i < numSeeds; ++i) {
        minValue = MIN(minValue, seeds[i].start);
    }

    printf("%lld\n", minValue);
}