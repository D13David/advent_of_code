#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "day21.h"

#define DAY 2

#define NUM_OPERATIONS (sizeof(data)/sizeof(data[0]))

#define MAKE_ID(name) hash((name[0] << 24) | (name[1] << 16) | (name[2] << 8) | name[3], 0)

typedef enum { false, true } bool;

typedef enum opType
{
	MUL, DIV, ADD, SUB, CONST
} opType_t;

typedef struct op
{
	unsigned long id;
	opType_t type;
	union
	{
		long long value;
		struct {
			unsigned long operand1;
			unsigned long operand2;
		};
	};
} op_t;

bool solveList(void);
void rearangeRemaningOperations(void);
void parseOperations(void);
op_t* findOperation(unsigned long id, bool searchWholeSpace);
unsigned long hash(unsigned long hash, int value);

op_t operationsBuffer[4096];
int numOperations;
int barrier;
op_t* operations;

main()
{
	bool solved;
	op_t* root;

	parseOperations();

	operations = operationsBuffer;

	solved = solveList();
#if DAY == 2
	if (!solved)
	{
		rearangeRemaningOperations();
		solved = solveList();
	}
#endif

#if DAY == 1
	root = findOperation(MAKE_ID("root"), false);
#else
	root = findOperation(MAKE_ID("humn"), false);
#endif
	printf("%lld\n", root->value);

	return 0;
}

unsigned long hash(unsigned long hash, int value)
{
	hash = ((hash << 5) + hash) + ((value >> 24) & 0xff);
	hash = ((hash << 5) + hash) + ((value >> 16) & 0xff);
	hash = ((hash << 5) + hash) + ((value >> 8) & 0xff);
	hash = ((hash << 5) + hash) + ((value >> 0) & 0xff);
	return hash;
}

int cmp(const void* a, const void* b)
{
	const op_t* op1 = (const op_t*)a;
	const op_t* op2 = (const op_t*)b;
	return op2->type - op1->type;
}

op_t* addConstant(unsigned long id, long long value)
{
	op_t* op = &operationsBuffer[numOperations++];
	op->id = id;
	op->type = CONST;
	op->value = value;
	return op;
}

op_t* addOperation(unsigned long id, opType_t type, unsigned long operandID1, unsigned long operandID2)
{
	op_t* op = &operationsBuffer[numOperations++];
	op->id = id;
	op->type = type;
	op->operand1 = operandID1;
	op->operand2 = operandID2;
	return op;
}

op_t* findOperation(unsigned long id, bool searchWholeSpace)
{
	int i, max;

	max = barrier;
	if (searchWholeSpace) {
		max = numOperations;
	}

	for (i = 0; i < max; ++i)
	{
		if (operations[i].id == id) {
			return &operations[i];
		}
	}
	return NULL;
}

bool solveList(void)
{
	int i;
	op_t* op1, * op2, tmp;
	bool foundAnyConst = true;

	qsort(operations, numOperations, sizeof(op_t), cmp);

	barrier = 0;
	foundAnyConst = true;

	while (barrier < numOperations && foundAnyConst)
	{
		if (operations[barrier].type == CONST) {
			barrier++;
		}
		else
		{
			foundAnyConst = false;

			for (i = barrier; i < numOperations; ++i)
			{
				op1 = findOperation(operations[i].operand1, false);
				op2 = findOperation(operations[i].operand2, false);
				if (!op1 || !op2) {
					continue;
				}

#if DAY == 2
				if (op1->id == MAKE_ID("humn") || op2->id == MAKE_ID("humn")) {
					continue;
				}
#endif

				foundAnyConst = true;
				tmp = operations[i];
				tmp.type = CONST;

				switch (operations[i].type)
				{
				case MUL: tmp.value = op1->value * op2->value; break;
				case DIV: tmp.value = op1->value / op2->value; break;
				case ADD: tmp.value = op1->value + op2->value; break;
				case SUB: tmp.value = op1->value - op2->value; break;
				}

				operations[i] = operations[barrier];
				operations[barrier] = tmp;
				barrier = barrier + 1;
			}
		}
	}

	return barrier >= numOperations;
}

void rearangeRemaningOperations(void)
{
	int start;
	op_t* op1, * op2, * opTarget, * result;

	start = numOperations;

	result = findOperation(MAKE_ID("root"), true);
	result->type = SUB;
	opTarget = addConstant(MAKE_ID("root"), 0);

	bool lastOperation = false;
	while (!lastOperation)
	{
		op1 = findOperation(result->operand1, true);
		op2 = findOperation(result->operand2, true);

		if (op1->id == MAKE_ID("humn") || op2->id == MAKE_ID("humn"))
		{
			if (op1->id == MAKE_ID("humn")) {
				op1->type = ADD;
			}
			else {
				op2->type = ADD;
			}
			lastOperation = true;
		}

		if (op1->type == CONST)
		{
			addConstant(op1->id, op1->value);
			switch (result->type)
			{
			case MUL: opTarget = addOperation(op2->id, DIV, opTarget->id, op1->id); break;
			case DIV: opTarget = addOperation(op2->id, DIV, op1->id, opTarget->id); break;
			case ADD: opTarget = addOperation(op2->id, SUB, opTarget->id, op1->id); break;
			case SUB: opTarget = addOperation(op2->id, SUB, op1->id, opTarget->id); break;
			}
			result = op2;
		}
		else if (op2->type == CONST)
		{
			addConstant(op2->id, op2->value);
			switch (result->type)
			{
			case MUL: opTarget = addOperation(op1->id, DIV, opTarget->id, op2->id); break;
			case DIV: opTarget = addOperation(op1->id, MUL, opTarget->id, op2->id); break;
			case ADD: opTarget = addOperation(op1->id, SUB, opTarget->id, op2->id); break;
			case SUB: opTarget = addOperation(op1->id, ADD, opTarget->id, op2->id); break;
			}
			result = op1;
		}
	}

	operations = &operationsBuffer[start];
	numOperations = numOperations - start;
}

void parseOperations(void)
{
	int i;
	char buffer[64], operant, *tmp2;
	const char* tmp1;
	op_t* op;

	tmp1 = buffer;
	tmp2 = buffer + 32; 
	
	for (i = 0; i < NUM_OPERATIONS; ++i)
	{
		tmp1 = data[i];
		tmp2[0] = 0, tmp2 = strncat(tmp2, tmp1, 4);
		tmp1 += 6;

		op = &operationsBuffer[numOperations++];
		op->id = MAKE_ID(tmp2);

		if (*tmp1 >= '0' && *tmp1 <= '9')
		{
			op->type = CONST;
			op->value = atoi(tmp1);
		}
		else
		{
			tmp2[0] = 0, tmp2 = strncat(tmp2, tmp1, 4);
			op->operand1 = MAKE_ID(tmp2);
			tmp1 += 5;

			operant = *tmp1;
			tmp1 += 2;

			tmp2[0] = 0, tmp2 = strncat(tmp2, tmp1, 4);
			op->operand2 = MAKE_ID(tmp2);

			switch (operant)
			{
			case '*': op->type = MUL; break;
			case '/': op->type = DIV; break;
			case '+': op->type = ADD; break;
			case '-': op->type = SUB; break;
			}
		}
	}
}