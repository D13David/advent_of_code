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
        int pathLengthStartToEnd = 0;
        int pos = 0;
        while (1)
        {
            if (nodes[index[i]].name[2] == 'Z') 
            {
                pathLengths[i] = pathLengthStartToEnd;
                break;
            }

            if (instructions[pos] == 'L') {
                index[i] = nodes[index[i]].left;
            }
            else if (instructions[pos] == 'R') {
                index[i] = nodes[index[i]].right;
            }

            pos = (pos + 1) % numInstructions, ++pathLengthStartToEnd;
        }

#define VERIFY_LOOP_LENGTH 0

#if VERIFY_LOOP_LENGTH
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

            if (index[i] == endNodeIndex && sequenceIndex == pos) {
                break;
            }
        }
        
        // this seems to be true for all the input data: the target node is hit every "n" steps. the loop step 
        // count is identical to the number of steps needed to hit the target for the first time. since this can
        // be verified for all the input data we know a path hits the target again after "n" steps. loop detection
        // could be more involved, but luckily this condition is met for the input data
        assert(pathLengthStartToEnd == loopPathLength);
#endif
    }

    // with the path length known: e.g. path 1 hits the target node every "n" steps. after the second iteration 
    // 2*n steps are needed etc... Therefore finding the LCM for all the path lengths will give the total number of 
    // steps needed so that all paths are hitting a target node.
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