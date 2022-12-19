#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <Windows.h>

#include "day19.h"

#define DAY 2

#define NUM_BLUEPRINTS (sizeof(data)/sizeof(data[0]))
#define MAX_STATES 64
#define NUM_RESOURCE_TYPES 4
#if DAY == 1
#define NUM_MINUTES 24
#else
#define NUM_MINUTES 32
#endif

typedef enum robot
{
	ORE,
	CLAY,
	OBSIDIAN,
	GEODE
} robot_t;

typedef struct blueprint
{
	int oreRobotCostOre;
	int clayRobotCostOre;
	int obsidianRobotCostOre;
	int obsidianRobotCostClay;
	int geodeRobotCostOre;
	int geodeRobotCostObsidian;
} blueprint_t;

typedef struct state
{
	int time;
	int robots[NUM_RESOURCE_TYPES];
	int resources[NUM_RESOURCE_TYPES];
} state_t;

int findMaxGeodes(blueprint_t* blueprint);
void parseBlueprints(const blueprint_t* blueprints);

state_t states[MAX_STATES];
int numStates;

main() 
{
	int i, numBlueprints, result;
	blueprint_t blueprints[NUM_BLUEPRINTS];

	memset(&blueprints, 0, sizeof(blueprints));
	parseBlueprints(blueprints);

	DWORD dt = GetTickCount();

#if DAY == 1
	for (i = 0, result = 0; i < NUM_BLUEPRINTS; ++i)
	{
		result += (i + 1) * findMaxGeodes(&blueprints[i]);
	}
#else
	for (i = 0, result = 1; i < 3; ++i)
	{
		result *= findMaxGeodes(&blueprints[i]);
	}
#endif

	printf("%d ms\n", (GetTickCount() - dt));

	printf("%d\n", result);

	return 0;
}

void pushState(state_t state)
{
	assert(numStates < MAX_STATES);
	states[numStates++] = state;
}

state_t popState()
{
	return states[--numStates];
}

state_t harvestResources(state_t state)
{
	int i;
	for (i = 0; i < NUM_RESOURCE_TYPES; ++i)
	{
		state.resources[i] += state.robots[i];
	}
	return state;
}

int findMaxGeodes(blueprint_t* blueprint)
{
	int i, resourcesChanges, maxGeodes = 0, numGeodesUpperBound, timeBoost;
	state_t state, copy;

	memset(&state, 0, sizeof(state_t));
	state.time = NUM_MINUTES;
	state.robots[ORE] = 1;
	pushState(state);

	while (numStates > 0)
	{
		state = popState();

		if (state.resources[GEODE] > maxGeodes) {
			maxGeodes = state.resources[GEODE];
		}

		if (state.time == 0) {
			continue;
		}

		--state.time;

		timeBoost = state.robots[GEODE] + state.time;
		numGeodesUpperBound = state.resources[GEODE] + (timeBoost * (timeBoost + 1)) / 2;
		if (numGeodesUpperBound < maxGeodes) {
			continue;
		}

		if (state.resources[ORE] >= blueprint->geodeRobotCostOre && state.resources[OBSIDIAN] >= blueprint->geodeRobotCostObsidian)
		{
			copy = harvestResources(state);
			copy.resources[ORE] -= blueprint->geodeRobotCostOre;
			copy.resources[OBSIDIAN] -= blueprint->geodeRobotCostObsidian;
			copy.robots[GEODE] = copy.robots[GEODE] + 1;
			pushState(copy);
		}
		else if (state.robots[OBSIDIAN] < blueprint->geodeRobotCostObsidian && state.resources[ORE] >= blueprint->obsidianRobotCostOre && state.resources[CLAY] >= blueprint->obsidianRobotCostClay)
		{
			copy = harvestResources(state);
			copy.resources[ORE] -= blueprint->obsidianRobotCostOre;
			copy.resources[CLAY] -= blueprint->obsidianRobotCostClay;
			copy.robots[OBSIDIAN] = copy.robots[OBSIDIAN] + 1;
			pushState(copy);
		}
		else
		{
			if (state.robots[CLAY] < blueprint->obsidianRobotCostClay && state.resources[ORE] >= blueprint->clayRobotCostOre)
			{
				copy = harvestResources(state);
				copy.resources[ORE] -= blueprint->clayRobotCostOre;
				copy.robots[CLAY] = copy.robots[CLAY] + 1;
				pushState(copy);
			}

			if (state.robots[ORE] < blueprint->clayRobotCostOre && state.resources[ORE] >= blueprint->oreRobotCostOre)
			{
				copy = harvestResources(state);
				copy.resources[ORE] -= blueprint->oreRobotCostOre;
				copy.robots[ORE] = copy.robots[ORE] + 1;
				pushState(copy);
			}
		}

		pushState(harvestResources(state));
	}

	return maxGeodes;
}

void parseBlueprints(blueprint_t* blueprints)
{
	int i, num;

	for (i = 0; i < NUM_BLUEPRINTS; ++i)
	{
		sscanf(data[i], "Blueprint %d: Each ore robot costs %d ore. Each clay robot costs %d ore. Each obsidian robot costs %d ore and %d clay. Each geode robot costs %d ore and %d obsidian.", &num, 
			&blueprints[i].oreRobotCostOre, &blueprints[i].clayRobotCostOre,
			&blueprints[i].obsidianRobotCostOre, &blueprints[i].obsidianRobotCostClay,
			&blueprints[i].geodeRobotCostOre, &blueprints[i].geodeRobotCostObsidian);
	}
}