#include "day08.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>

#define PART            2

#define DATA_LENGTH     (sizeof(data)/sizeof(data[0]))
#define MAX_NODES       (DATA_LENGTH-2)
#define MAX_POSITIONS   16

typedef struct node_s
{
    char name[4];
    int left, right;
} node_t;

node_t nodes[MAX_NODES];

#if PART == 2
unsigned __int64 gcd(unsigned __int64 a, unsigned __int64 b)
{
    unsigned __int64 temp;
    while (b != 0)
    {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}
#endif

main()
{
    const char* instructions = data[0];

    for (int i = 2; i < sizeof(data) / sizeof(data[0]); ++i)
    {
        int result = sscanf(data[i], "%3[1-9A-Z]", nodes[i - 2].name);
        assert(result == 1);
    }

    for (int i = 2; i < sizeof(data) / sizeof(data[0]); ++i)
    {
        char names[3][4];
        int result = sscanf(data[i], "%3[1-9A-Z] = (%3[1-9A-Z], %3[1-9A-Z])", &names[0], &names[1], &names[2]);
        assert(result == 3);

        for (int j = 0; j < MAX_NODES; ++j) 
        {
            if (!strncmp(nodes[j].name, names[1], 3)) {
                nodes[i - 2].left = j;
            }
            if (!strncmp(nodes[j].name, names[2], 3)) {
                nodes[i - 2].right = j;
            }
        }
    }

    int index[MAX_POSITIONS], positions = 0;

    for (int i = 0; i < MAX_NODES; ++i)
    {
#if PART == 1
        if (!strncmp(nodes[i].name, "AAA", 3)) 
        {
            index[positions++] = i;
            break;
        }
#else
        if (nodes[i].name[2] == 'A') {
            index[positions++] = i;
        }
#endif
    }

    unsigned __int64 count = 0;
    const size_t numInstructions = strlen(instructions);

#if PART == 2
    unsigned __int64 pathLengths[MAX_POSITIONS];

    for (int i = 0; i < positions; ++i)
    {
        // find first time we hit an end node starting from start-point
        int pos = 0;
        while (1)
        {
            if (nodes[index[i]].name[2] == 'Z') {
                break;
            }

            if (instructions[pos] == 'L') {
                index[i] = nodes[index[i]].left;
            }
            else if (instructions[pos] == 'R') {
                index[i] = nodes[index[i]].right;
            }

            pos = (pos + 1) % numInstructions;
        }

        // now we travel along the path until we loop back to the starting position
        int endNodeIndex = index[i];
        int sequenceIndex = pos;
        int loopPathLength = 0;
        while (1)
        {
            if (instructions[pos] == 'L') {
                index[i] = nodes[index[i]].left;
            }
            else if (instructions[pos] == 'R') {
                index[i] = nodes[index[i]].right;
            }

            pos = (pos + 1) % numInstructions, ++loopPathLength;

            if (index[i] == endNodeIndex && sequenceIndex == pos)
            {
                pathLengths[i] = loopPathLength;
                break;
            }
        }
    }

    // with all the path lengths (**A ---> **Z ---loop--> **Z ...) we need to find the LCM to calculate the point
    // where all paths hit and end node together
    for (int i = 1; i < positions; ++i)
    {
        unsigned __int64 tmp = gcd(pathLengths[i - 1], pathLengths[i]);
        pathLengths[i] = (pathLengths[i - 1] * pathLengths[i]) / tmp;
    }
    count = pathLengths[positions - 1];
#else
    assert(positions == 1);
    while (1)
    {
        if (instructions[count % numInstructions] == 'L') {
            index[0] = nodes[index[0]].left;
        }
        else if (instructions[count % numInstructions] == 'R') {
            index[0] = nodes[index[0]].right;
        }

        ++count;

        if (!strncmp(nodes[index[0]].name, "ZZZ", 3)) {
            break;
        }
    }
#endif

    printf("%lld\n", count);
}