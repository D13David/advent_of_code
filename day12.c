#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

#define PART 2

const char* data1[] =
{
    "start-A",
    "start-b",
    "A-c",
    "A-b",
    "b-d",
    "A-end",
    "b-end"
};

const char* data2[] =
{
    "dc-end",
    "HN-start",
    "start-kj",
    "dc-start",
    "dc-HN",
    "LN-dc",
    "HN-end",
    "kj-sa",
    "kj-HN",
    "kj-dc"
};

const char* data3[] =
{
    "fs-end",
    "he-DX",
    "fs-he",
    "start-DX",
    "pj-DX",
    "end-zg",
    "zg-sl",
    "zg-pj",
    "pj-he",
    "RW-he",
    "fs-DX",
    "pj-RW",
    "zg-RW",
    "start-pj",
    "he-WI",
    "zg-he",
    "pj-fs",
    "start-RW"
};

const char* data4[] =
{
    "HF-qu",
    "end-CF",
    "CF-ae",
    "vi-HF",
    "vt-HF",
    "qu-CF",
    "hu-vt",
    "CF-pk",
    "CF-vi",
    "qu-ae",
    "ae-hu",
    "HF-start",
    "vt-end",
    "ae-HF",
    "end-vi",
    "vi-vt",
    "hu-start",
    "start-ae",
    "CS-hu",
    "CF-vt"
};

#define data data4

#define MAX_NAME_LENGTH 6
#define MAX_NODES 15
#define MAX_PATH_LENGTH 42
#define EDGE_POOL_ELEMENTS 128

typedef struct edge_t
{
    int index : 30;
    int small : 1;
    struct edge_t* next;
} edge;

edge edgePool[EDGE_POOL_ELEMENTS];
int edgeAllocIndex;

char nodes[MAX_NODES][MAX_NAME_LENGTH];
edge* edges[MAX_NODES];
int numNodes;

int cavesVisited[MAX_NODES];
int startNodeIndex;

int nodeIndex(const char* node, int length)
{
    for (int i = 0; i < numNodes; ++i)
    {
        if (!strncmp(nodes[i], node, length))
            return i;
    }
    return -1;
}

int addUniqueNode(const char* node, int length)
{
    int index = nodeIndex(node, length);
    if (index == -1)
    {
        assert(numNodes < MAX_NODES && "too many nodes. increase pool");
        strncpy_s(nodes[numNodes], MAX_NAME_LENGTH, node, length);
        index = numNodes++;
    }
    return index;
}

void addEdge(int node, int target)
{
    assert(edgeAllocIndex < EDGE_POOL_ELEMENTS && "edge pool is empty");
    struct edge_t* edge = &edgePool[edgeAllocIndex++];
    edge->index = target;
    edge->small = islower(nodes[node][0]) > 0;
    edge->next = edges[node];
    edges[node] = edge;
}

void initialize()
{
    for (int i = 0; i < _countof(data); ++i)
    {
        char* split = strchr(data[i], '-');
        int node1 = addUniqueNode(data[i], split - data[i]);
        int node2 = addUniqueNode(split + 1, -1);
        addEdge(node1, node2);
        addEdge(node2, node1);
    }
}

void searchAllPaths(int index, int endIndex, int* numPathsFound)
{
    cavesVisited[index]++;

    if (index == endIndex)
    {
        (*numPathsFound)++;
    }
    else
    {
        for (edge* e = edges[index]; e; e = e->next)
        {
            bool canEnter = e->index != startNodeIndex;
            if (canEnter && edges[e->index]->small)
            {
#if PART == 1
                canEnter &= cavesVisited[e->index] == 0;
#else
                if (cavesVisited[e->index] > 0)
                {
                    for (int i = 0; i < numNodes; ++i)
                    {
                        if (edges[i]->small && cavesVisited[i] == 2)
                        {
                            canEnter = false;
                            break;
                        }
                    }
                }
#endif
            }

            if (canEnter)
            {
                searchAllPaths(e->index, endIndex, numPathsFound);
            }
        }
    }

    cavesVisited[index]--;
}

int main()
{
    initialize();
    startNodeIndex = nodeIndex("start", -1);
    int numPaths = 0;
    searchAllPaths(startNodeIndex, nodeIndex("end", -1), &numPaths);
    printf("%d\n", numPaths);
}