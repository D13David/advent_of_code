#include "day19.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define PART                2

#define CMP_LESS_THAN       0
#define CMP_GREATER_THAN    1
#define CMP_NONE            2

#define OP_CALL             0
#define OP_ACCEPT           1
#define OP_REJECT           2

#define CATEGORY_X          0
#define CATEGORY_M          1
#define CATEGORY_A          2
#define CATEGORY_S          3

#define MAX_PARTS           200
#define MAX_WORKFLOWS       550
#define MAX_CONDITIONS      4
#define MAX_NAME_LENGTH     8

typedef struct condition_s
{
    char name[MAX_NAME_LENGTH];
    unsigned int cmp      : 2;
    unsigned int op       : 2;
    unsigned int category : 2;
    int value;
} condition_t;

typedef struct workflow_s
{
    char name[MAX_NAME_LENGTH];
    condition_t conditions[MAX_CONDITIONS];
    unsigned int numConditions;
} workflow_t;

typedef struct part_s
{
    int values[4];
} part_t;

typedef struct range_s
{
    int min;
    int max;
} range_t;

const workflow_t* findWorkflow(const char* name, const workflow_t* workflows, int numWorkflows)
{
    for (int i = 0; i < numWorkflows; ++i)
    {
        if (!strcmp(workflows[i].name, name)) {
            return &workflows[i];
        }
    }
    return NULL;
}

void parseWorkflow(const char* line, workflow_t* workflow)
{
    char buffer[255];
    int result = sscanf(line, "%8[^{]{%255[^}]}", workflow->name, buffer);
    assert(result == 2);

    workflow->numConditions = 0;

    char* token = strtok(buffer, ",");
    while (token)
    {
        assert(workflow->numConditions < MAX_CONDITIONS);
        condition_t* condition = &workflow->conditions[workflow->numConditions++];
        char* pos = strchr(token, ':');
        if (pos != NULL)
        {
            switch (*token++)
            {
            case 'x': condition->category = CATEGORY_X; break;
            case 'm': condition->category = CATEGORY_M; break;
            case 'a': condition->category = CATEGORY_A; break;
            case 's': condition->category = CATEGORY_S; break;
            }

            if (*token++ == '<') {
                condition->cmp = CMP_LESS_THAN;
            }
            else {
                condition->cmp = CMP_GREATER_THAN;
            }

            condition->value = atoi(token);

            strncpy(condition->name, pos + 1, MAX_NAME_LENGTH);
        }
        else
        {
            condition->cmp = CMP_NONE;
            condition->op = OP_CALL;
            strncpy(condition->name, token, MAX_NAME_LENGTH);
        }

        if (*condition->name == 'A') {
            condition->op = OP_ACCEPT;
        }
        else if (*condition->name == 'R') {
            condition->op = OP_REJECT;
        }
        else {
            condition->op = OP_CALL;
        }

        token = strtok(NULL, ",");
    }
}

void parsePart(const char* line, part_t* part)
{
    part->values[CATEGORY_X] = 0;
    part->values[CATEGORY_M] = 0;
    part->values[CATEGORY_A] = 0;
    part->values[CATEGORY_S] = 0;

    char buffer[255];
    size_t len = strlen(line) - 2;
    strncpy(buffer, line + 1, len);
    buffer[len] = '\0';

    char* token = strtok(buffer, ",");
    while (token)
    {
        assert(token[1] == '=');
        int value = atoi(token + 2);

        switch (*token++)
        {
        case 'x': part->values[CATEGORY_X] = value; break;
        case 'm': part->values[CATEGORY_M] = value; break;
        case 'a': part->values[CATEGORY_A] = value; break;
        case 's': part->values[CATEGORY_S] = value; break;
        }

        token = strtok(NULL, ",");
    }
}

int executeWorkflowOnPart(const part_t* part, const workflow_t* workflows, int numWorkflows)
{
    const workflow_t* workflow = findWorkflow("in", workflows, numWorkflows);

start:
    for (unsigned int j = 0; j < workflow->numConditions; ++j)
    {
        const condition_t* cond = &workflow->conditions[j];
        int canInvoke = 1;
        if (cond->cmp == CMP_GREATER_THAN)
        {
            canInvoke = part->values[cond->category] > cond->value;
        }
        else if (cond->cmp == CMP_LESS_THAN)
        {
            canInvoke = part->values[cond->category] < cond->value;
        }

        if (canInvoke)
        {
            if (cond->op == OP_ACCEPT || cond->op == OP_REJECT)
            {
                return cond->op == OP_ACCEPT;
            }
            else
            {
                assert(cond->op == OP_CALL);
                const workflow_t* prev = workflow;
                workflow = findWorkflow(cond->name, workflows, numWorkflows);
                assert(workflow);
                goto start;
            }
        }
    }

    return -1;
}

#if PART == 2
unsigned __int64 countPossibleCombinations(range_t ranges[4], const char* name, const workflow_t* workflows, int numWorkflows)
{
    if (*name == 'R') {
        return 0;
    }

    if (*name == 'A') 
    {
        return (unsigned __int64)(ranges[0].max - ranges[0].min + 1) *
               (ranges[1].max - ranges[1].min + 1) *
               (ranges[2].max - ranges[2].min + 1) *
               (ranges[3].max - ranges[3].min + 1);
    }

    const workflow_t* workflow = findWorkflow(name, workflows, numWorkflows);
    assert(workflow != NULL);

    unsigned __int64 result = 0;
    for (int i = 0; i < workflow->numConditions; ++i)
    {
        const condition_t* cond = &workflow->conditions[i];
        if (cond->cmp == CMP_NONE) {
            result = result + countPossibleCombinations(ranges, cond->name, workflows, numWorkflows); // for same range
        } 
        else if (cond->cmp == CMP_GREATER_THAN && ranges[cond->category].max > cond->value)
        {
            if (ranges[cond->category].min < cond->value)
            {
                range_t partition[4];
                for (int j = 0; j < 4; ++j) {
                    partition[j] = ranges[j];
                }
                partition[cond->category].min = cond->value + 1;
                ranges[cond->category].max = cond->value;
                result = result + countPossibleCombinations(partition, cond->name, workflows, numWorkflows);
            }
            else {
                return result + countPossibleCombinations(ranges, cond->name, workflows, numWorkflows);
            }
        }
        else if (cond->cmp == CMP_LESS_THAN && ranges[cond->category].min < cond->value)
        {
            if (ranges[cond->category].max > cond->value)
            {
                range_t partition[4];
                for (int j = 0; j < 4; ++j) {
                    partition[j] = ranges[j];
                }
                partition[cond->category].max = cond->value - 1;
                ranges[cond->category].min = cond->value;
                result = result + countPossibleCombinations(partition, cond->name, workflows, numWorkflows);
            }
            else {
                return result + countPossibleCombinations(ranges, cond->name, workflows, numWorkflows);
            }
        }
    }

    return result;
}
#endif

main()
{
    workflow_t workflows[MAX_WORKFLOWS];
    int numWorkflows = 0;

    part_t parts[MAX_PARTS];
    int numParts = 0;

    int i = 0;
    for (; data[i] != ""; ++i)
    {
        assert(numWorkflows < MAX_WORKFLOWS);
        parseWorkflow(data[i], &workflows[numWorkflows++]);
    }

    ++i; // skip empty line

    for (; i < sizeof(data) / sizeof(data[0]); ++i)
    {
        assert(numParts < MAX_PARTS);
        parsePart(data[i], &parts[numParts++]);
    }

    unsigned __int64 sum = 0;
#if PART == 1
    for (int i = 0; i < numParts; ++i)
    {
        int result = executeWorkflowOnPart(&parts[i], workflows, numWorkflows);
        assert(result >= 0);
        if (result == 1)
        {
            sum = sum + parts[i].values[CATEGORY_X]
                      + parts[i].values[CATEGORY_M]
                      + parts[i].values[CATEGORY_A]
                      + parts[i].values[CATEGORY_S];
        }
    }
#else
    range_t ranges[4];
    for (int i = 0; i < 4; ++i)
    {
        ranges[i].min = 1;
        ranges[i].max = 4000;
    }
    sum = countPossibleCombinations(ranges,"in", workflows, numWorkflows);
#endif
    printf("%llu\n", sum);
}