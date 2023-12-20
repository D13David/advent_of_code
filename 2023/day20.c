#include "day20.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define DEBUG            1
#define DEBUG_PRINT_FLOW 0

#define PART             2

#if PART == 1
#define MAX_LOOPS        1000
#else
#define MAX_LOOPS        2147483647
#endif

#define MAX_MODULES      64
#define MAX_TARGETS      8
#define MAX_INPUTS       16
#define MAX_CALL_STATES  128

#define PULSE_LOW        0
#define PULSE_HIGHT      1

typedef struct inputState_s
{
    unsigned long name;
    int state;
} inputState_t;

typedef struct callState_s
{
    struct module_s* self;
    struct module_s* source;
    int pulse;
} callState_t;

typedef struct module_s
{
    unsigned long name;
#if DEBUG
    char debugName[16];
#endif
    unsigned long targets[MAX_TARGETS];
    int numTargets;
    inputState_t inputState[MAX_INPUTS];
    int numInputStates;
    __int64 (*think)(callState_t);
} module_t;

module_t modules[MAX_MODULES];
int numModules;

callState_t callStates[MAX_CALL_STATES];
int bottom, top, numCallStates;

int buttonPressed = 1;

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

unsigned long djb2(const char* str, unsigned int maxLength)
{
    unsigned long hash = 5381;
    for (unsigned int c = *str, i = 0; c && i < maxLength; c = *++str, ++i) 
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

module_t* findModule(unsigned int id)
{
    for (int i = 0; i < numModules; ++i)
    {
        if (modules[i].name == id) {
            return &modules[i];
        }
    }
    return NULL;
}

int hasTarget(const module_t* module, const module_t* target)
{
    for (int i = 0; i < module->numTargets; ++i)
    {
        if (module->targets[i] == target->name) {
            return 1;
        }
    }
    return 0;
}

void pushCallState(int pulse, module_t* self, module_t* source)
{
    assert(numCallStates < MAX_CALL_STATES);
    callStates[top++] = (callState_t) {
        .pulse = pulse, .self = self, .source = source
    };

    if (top >= MAX_CALL_STATES) {
        top = 0;
    }

    ++numCallStates;
}

callState_t* popCallState()
{
    if (numCallStates == 0) {
        return NULL;
    }

    callState_t* result = &callStates[bottom++];

    if (bottom >= MAX_CALL_STATES) {
        bottom = 0;
    }

    --numCallStates;

    return result;
}

__int64 thinkBroadcaster(callState_t callState)
{
#if DEBUG_PRINT_FLOW
    printf("%s\n", callState.self->debugName);
#endif

    for (int i = 0; i < callState.self->numTargets; ++i)
    {
        module_t* target = findModule(callState.self->targets[i]);
        assert(target != NULL);
        pushCallState(callState.pulse, target, callState.self);
    }
    return -1;
}

__int64 thinkConjunction(callState_t callState)
{
#if DEBUG_PRINT_FLOW
    printf("&%s\n", callState.self->debugName);
#endif

    inputState_t* inputState = NULL;
    for (int i = 0; i < callState.self->numInputStates; ++i)
    {
        if (callState.self->inputState[i].name == callState.source->name)
        {
            inputState = &callState.self->inputState[i];
            break;
        }
    }

    assert(inputState != NULL);

    inputState->state = callState.pulse;

    int allInputsHighState = 1;
    for (int i = 0; allInputsHighState && i < callState.self->numInputStates; ++i)
    {
        allInputsHighState = callState.self->inputState[i].state == PULSE_HIGHT;
    }

    int targetPulse = allInputsHighState ? PULSE_LOW : PULSE_HIGHT;

    for (int i = 0; i < callState.self->numTargets; ++i)
    {
        module_t* target = findModule(callState.self->targets[i]);
        assert(target != NULL);
        pushCallState(targetPulse, target, callState.self);
    }
    return -1;
}

__int64 thinkFlipflop(callState_t callState)
{
#if DEBUG_PRINT_FLOW
    printf("%%%s\n", callState.self->debugName);
#endif

    if (callState.pulse == PULSE_HIGHT) {
        return -1;
    }

    callState.self->inputState[0].state = !callState.self->inputState[0].state;

    for (int i = 0; i < callState.self->numTargets; ++i)
    {
        module_t* target = findModule(callState.self->targets[i]);
        assert(target != NULL);
        pushCallState(callState.self->inputState[0].state, target, callState.self);
    }
    return -1;
}

__int64 thinkOutput(callState_t callState)
{
#if DEBUG_PRINT_FLOW
    printf("%s\n", callState.self->debugName);
#endif

    __int64 result = -1;

#if PART == 2
    assert(callState.self->numInputStates == 1);
    module_t* module = findModule(callState.self->inputState[0].name);

    static unsigned __int64 cycleLength[4];

    int allCyclesFound = 1;
    for (int i = 0; i < module->numInputStates; ++i)
    {
        if (module->inputState[i].state == PULSE_HIGHT) 
        {
            if (cycleLength[i] == 0) {
                cycleLength[i] = buttonPressed;
            }
        }
        allCyclesFound &= cycleLength[i] != 0;
    }
    if (allCyclesFound)
    {
        for (int i = 1; i < 4; ++i)
        {
            unsigned __int64 tmp = gcd(cycleLength[i - 1], cycleLength[i]);
            cycleLength[i] = (cycleLength[i - 1] * cycleLength[i]) / tmp;
        }
        result = cycleLength[3];
    }
#endif
    return result;
}

void parseModule(const char* line)
{
    assert(numModules < MAX_MODULES);
    module_t* module = &modules[numModules++];

    char* targetList = strstr(line, "->");
    assert(targetList != NULL);

    if (*line == '%') 
    {
        module->think = &thinkFlipflop;
        module->inputState[0].state = 0;
        module->numInputStates = 1;
        ++line;
    }
    else if (*line == '&') 
    {
        module->think = &thinkConjunction;
        ++line;
    }
    else {
        module->think = &thinkBroadcaster;
    }

    module->name = djb2(line, (unsigned int)(targetList - line - 1));
#if DEBUG
    strncpy_s(module->debugName, sizeof(module->debugName), line, targetList - line - 1);
#endif

    char buffer[128];
    strcpy_s(buffer, sizeof(buffer), targetList + 3);
    char* token = strtok(buffer, ", ");
    while (token)
    {
        assert(module->numTargets < MAX_TARGETS);
        module->targets[module->numTargets++] = djb2(token, -1);
        token = strtok(NULL, ", ");
    }
}

main()
{
    // load modules
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
        parseModule(data[i]);
    }

    assert(numModules < MAX_MODULES);
    modules[numModules].name = djb2("rx", -1);
#if DEBUG
    strcpy(modules[numModules].debugName, "rx");
#endif
    modules[numModules].think = &thinkOutput;
    numModules++;

    // initialize input states for each module
    for (int i = 0; i < numModules; ++i)
    {
        for (int j = 0; j < numModules; ++j)
        {
            if (hasTarget(&modules[j], &modules[i]))
            {
                assert(modules[i].numInputStates < MAX_INPUTS);
                inputState_t* inputState = &modules[i].inputState[modules[i].numInputStates++];
                inputState->name = modules[j].name;
                inputState->state = 0;
            }
        }
    }

    module_t* module = findModule(djb2("broadcaster", -1));
    assert(module != NULL);

#if PART == 1
    int pulseCounter[2];
    pulseCounter[0] = 0;
    pulseCounter[1] = 0;
#endif

    for (int i = 0; i < MAX_LOOPS; ++i, ++buttonPressed)
    {
        pushCallState(PULSE_LOW, module, NULL);

        while (numCallStates != 0)
        {
            callState_t* callState = popCallState();
#if PART == 1
            pulseCounter[callState->pulse]++;
#endif
            assert(callState != NULL);
            __int64 result = callState->self->think(*callState);
            if (result != -1) 
            {
#if PART == 2
                printf("%lld", result);
                i = MAX_LOOPS - 1;
                break;
#endif
            }
        }
    }

#if PART == 1
    printf("%d\n", pulseCounter[0] * pulseCounter[1]);
#endif
}