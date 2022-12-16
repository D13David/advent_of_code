#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "DAY16.H"

#define DAY 2

#define NUM_VALVES (sizeof(data)/sizeof(data[0]))
#define MAX_EDGES 256
#if DAY == 1
#define MAX_TIME 30
#else
#define MAX_TIME 26
#endif

typedef struct edge_t
{
	int index;
	struct edge_t* next;
} edge;

typedef struct valve_t
{
	char name[3];
	int rate : 7;
	int opened : 1;
	struct edge_t* edges;
} valve;

edge edges[MAX_EDGES];
valve valves[NUM_VALVES];
int numValves, numEdges;
int dist[NUM_VALVES][NUM_VALVES];

int findValveIndex(const char* name);
void parseValves(void);
int searchAllPaths(int index1, int index2, int time1, int time2);

main()
{
	int i, j, k, startIndex, maxFlowRate = 0;
	edge* edge;

	parseValves();

	for (i = 0; i < NUM_VALVES; ++i)
		for (j = 0; j < NUM_VALVES; ++j)
			dist[i][j] = 0xffff;

	for (i = 0; i < NUM_VALVES; ++i)
	{
		for (edge = valves[i].edges; edge; edge = edge->next)
		{
			dist[i][edge->index] = 1;
		}
		dist[i][i] = 0;
	}

	for (k = 0; k < NUM_VALVES; ++k) {
		for (i = 0; i < NUM_VALVES; ++i) {
			for (j = 0; j < NUM_VALVES; ++j) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}

	startIndex = findValveIndex("AA");

#if DAY == 1
	printf("%d\n", searchAllPaths(startIndex, 0, MAX_TIME, 0));
#else
	printf("%d\n", searchAllPaths(startIndex, startIndex, MAX_TIME, MAX_TIME));
#endif

	return 0;
}

int findValveIndex(const char* name)
{
	int i;

	for (i = 0; i < NUM_VALVES; ++i)
	{
		if (!strcmp(valves[i].name, name)) {
			return i;
		}
	}

	return -1;
}

void parseValves(void)
{
	int i, rate;
	char *p, buffer[255];
	valve* current;
	edge* currentEdge;

	for (i = 0; i < NUM_VALVES; ++i)
	{
		current = &valves[numValves++];
		sscanf(data[i], "Valve %s has flow rate=%d", current->name, &rate);
		current->rate = rate;
		current->opened = 0;
		current->edges = NULL;
	}

	for (i = 0; i < NUM_VALVES; ++i)
	{
		p = strstr(data[i], "to valve") + 9;
		if (*p == ' ') {
			++p;
		}
		strcpy(buffer, p);
		p = strtok(buffer, ", ");
		while (p)
		{
			assert(numEdges < MAX_EDGES);
			currentEdge = &edges[numEdges++];
			currentEdge->next = valves[i].edges;
			currentEdge->index = findValveIndex(p);
			valves[i].edges = currentEdge;
			p = strtok(NULL, ", ");
		}
	}
}

int searchAllPaths(int index1, int index2, int time1, int time2)
{
	int i, timeLeft, totalFlowRate, maxFlowRate = 0;

	if (time1 <= 0 && time2 <= 0) {
		return 0;
	}

	for (i = 0; i < NUM_VALVES; ++i)
	{
		if (valves[i].opened || valves[i].rate == 0) {
			continue;
		}

		valves[i].opened = 1;

		if (time1 > time2)
		{
			timeLeft = time1 - dist[index1][i] - 1;
			totalFlowRate = valves[i].rate * timeLeft + searchAllPaths(i, index2, timeLeft, time2);
		}
		else
		{
			timeLeft = time2 - dist[index2][i] - 1;
			totalFlowRate = valves[i].rate * timeLeft + searchAllPaths(index1, i, time1, timeLeft);
		}

		if (totalFlowRate > maxFlowRate) {
			maxFlowRate = totalFlowRate;
		}

		valves[i].opened = 0;
	}

	return maxFlowRate;
}