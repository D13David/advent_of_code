#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>

#define PART 1

const char* data[] =
{
	"inp w",
	"mul x 0",
	"add x z",
	"mod x 26",
	"div z 1",
	"add x 11",
	"eql x w",
	"eql x 0",
	"mul y 0",
	"add y 25",
	"mul y x",
	"add y 1",
	"mul z y",
	"mul y 0",
	"add y w",
	"add y 14",
	"mul y x",
	"add z y",

	"inp w",
	"mul x 0",
	"add x z",
	"mod x 26",
	"div z 1",
	"add x 13",
	"eql x w",
	"eql x 0",
	"mul y 0",
	"add y 25",
	"mul y x",
	"add y 1",
	"mul z y",
	"mul y 0",
	"add y w",
	"add y 8",
	"mul y x",
	"add z y",

	"inp w",
	"mul x 0",
	"add x z",
	"mod x 26",
	"div z 1",
	"add x 11",
	"eql x w",
	"eql x 0",
	"mul y 0",
	"add y 25",
	"mul y x",
	"add y 1",
	"mul z y",
	"mul y 0",
	"add y w",
	"add y 4",
	"mul y x",
	"add z y",

	"inp w",
	"mul x 0",
	"add x z",
	"mod x 26",
	"div z 1",
	"add x 10",
	"eql x w",
	"eql x 0",
	"mul y 0",
	"add y 25",
	"mul y x",
	"add y 1",
	"mul z y",
	"mul y 0",
	"add y w",
	"add y 10",
	"mul y x",
	"add z y",

	"inp w",
	"mul x 0",
	"add x z",
	"mod x 26",
	"div z 26",
	"add x -3",
	"eql x w",
	"eql x 0",
	"mul y 0",
	"add y 25",
	"mul y x",
	"add y 1",
	"mul z y",
	"mul y 0",
	"add y w",
	"add y 14",
	"mul y x",
	"add z y",

	"inp w",
	"mul x 0",
	"add x z",
	"mod x 26",
	"div z 26",
	"add x -4",
	"eql x w",
	"eql x 0",
	"mul y 0",
	"add y 25",
	"mul y x",
	"add y 1",
	"mul z y",
	"mul y 0",
	"add y w",
	"add y 10",
	"mul y x",
	"add z y",

	"inp w",
	"mul x 0",
	"add x z",
	"mod x 26",
	"div z 1",
	"add x 12",
	"eql x w",
	"eql x 0",
	"mul y 0",
	"add y 25",
	"mul y x",
	"add y 1",
	"mul z y",
	"mul y 0",
	"add y w",
	"add y 4",
	"mul y x",
	"add z y",

	"inp w",
	"mul x 0",
	"add x z",
	"mod x 26",
	"div z 26",
	"add x -8",
	"eql x w",
	"eql x 0",
	"mul y 0",
	"add y 25",
	"mul y x",
	"add y 1",
	"mul z y",
	"mul y 0",
	"add y w",
	"add y 14",
	"mul y x",
	"add z y",

	"inp w",
	"mul x 0",
	"add x z",
	"mod x 26",
	"div z 26",
	"add x -3",
	"eql x w",
	"eql x 0",
	"mul y 0",
	"add y 25",
	"mul y x",
	"add y 1",
	"mul z y",
	"mul y 0",
	"add y w",
	"add y 1",
	"mul y x",
	"add z y",

	"inp w",
	"mul x 0",
	"add x z",
	"mod x 26",
	"div z 26",
	"add x -12",
	"eql x w",
	"eql x 0",
	"mul y 0",
	"add y 25",
	"mul y x",
	"add y 1",
	"mul z y",
	"mul y 0",
	"add y w",
	"add y 6",
	"mul y x",
	"add z y",

	"inp w",
	"mul x 0",
	"add x z",
	"mod x 26",
	"div z 1",
	"add x 14",
	"eql x w",
	"eql x 0",
	"mul y 0",
	"add y 25",
	"mul y x",
	"add y 1",
	"mul z y",
	"mul y 0",
	"add y w",
	"add y 0",
	"mul y x",
	"add z y",

	"inp w",
	"mul x 0",
	"add x z",
	"mod x 26",
	"div z 26",
	"add x -6",
	"eql x w",
	"eql x 0",
	"mul y 0",
	"add y 25",
	"mul y x",
	"add y 1",
	"mul z y",
	"mul y 0",
	"add y w",
	"add y 9",
	"mul y x",
	"add z y",

	"inp w",
	"mul x 0",
	"add x z",
	"mod x 26",
	"div z 1",
	"add x 11",
	"eql x w",
	"eql x 0",
	"mul y 0",
	"add y 25",
	"mul y x",
	"add y 1",
	"mul z y",
	"mul y 0",
	"add y w",
	"add y 13",
	"mul y x",
	"add z y",

	"inp w",
	"mul x 0",
	"add x z",
	"mod x 26",
	"div z 26",
	"add x -12",
	"eql x w",
	"eql x 0",
	"mul y 0",
	"add y 25",
	"mul y x",
	"add y 1",
	"mul z y",
	"mul y 0",
	"add y w",
	"add y 12",
	"mul y x",
	"add z y",
};

enum mnem_t
{
	INP, ADD, MUL, DIV, MOD, EQL, PSH
};

enum regs_t
{
	W, X, Y, Z, S
};

struct context_t
{
	int regs[5];
	int stack[64];
	_int64 div;
	_int64 input;
};

typedef struct op_t
{
	unsigned short code : 3;
	unsigned short reg1 : 2;
	unsigned short imm : 1;
	union {
		unsigned short reg2 : 4;
		short value : 8;
	};
} op;

#define INVALID_OP_CODE 7

struct context_t context;

int compile(const char* src[], int length, struct op_t** bytecode, bool patchCode)
{
	int extraLength = 0;
	if (patchCode)
		extraLength += 7 * 1 + 7 * 2; // incrementing sequence (1) push, decrementing (1) push, (2) add

	*(bytecode) = (struct op_t*)malloc((length + 1 + extraLength) * sizeof(struct op_t));
	struct op_t* start = *bytecode;

	int blockStartIndex = 0;
	for (int i = 0, instructionIndex = 0; i < length; ++i, ++instructionIndex)
	{
		const char* line = data[i];
		char mnem[4] = { 0 };
		strncpy(mnem, line, 3);

		struct op_t op = { 0xffff };
		if (!strcmp(mnem, "inp"))
		{
			op.code = INP;
			instructionIndex = 0;
			blockStartIndex = start - *bytecode;

			// patch previous block
			if (patchCode && blockStartIndex > 0)
			{
				struct op_t patchOp = { 0xffff };
				patchOp.code = PSH;
				patchOp.reg1 = W;
				*(start) = patchOp; ++start;
				++blockStartIndex;
			}
		}
		else if (!strcmp(mnem, "add"))
			op.code = ADD;
		else if (!strcmp(mnem, "mul"))
			op.code = MUL;
		else if (!strcmp(mnem, "div"))
			op.code = DIV;
		else if (!strcmp(mnem, "mod"))
			op.code = MOD;
		else if (!strcmp(mnem, "eql"))
			op.code = EQL;
		line += 4;

		op.reg1 = *line - 'w';
		line += 2;

		if (strcmp(mnem, "inp") && strcmp(mnem, "psh"))
		{
			bool isNegative = *line == '-';
			if (isNegative) ++line;
			if (*line >= '0' && *line <= '9')
			{
				op.value = atoi(line);
				if (isNegative)
					op.value = -op.value;
				op.imm = 1;
			}
			else
			{
				op.reg2 = *line - 'w';
				op.imm = 0;
			}
		}

		*(start) = op; ++start;

		// we need to patch this block
		if (patchCode && (instructionIndex == 5 && op.imm == 1 && op.value < 0))
		{
			struct op_t* readInput = *(bytecode)+blockStartIndex;

			/*
				we want to patch the sequence to always satisfy the z==w test and push the value of x to the stack

				original	patched
				inp w		mul w 0
				mul x 0
				add x z
				mod x 26
				div z 26
				add x -3
							add w, x
				eql x w
				eql x 0
				mul y 0
				...
							psh w
			*/

			struct op_t patchOp = { 0xffff };
			patchOp.code = MUL;
			patchOp.reg1 = W;
			patchOp.imm = 1;
			patchOp.value = 0;
			*readInput = patchOp;

			patchOp.code = ADD;
			patchOp.reg1 = W;
			patchOp.reg2 = X;
			patchOp.imm = 0;
			(*start) = patchOp; ++start;
		}
	}

	if (patchCode)
	{
		struct op_t patchOp = { 0xffff };
		patchOp.code = PSH;
		patchOp.reg1 = W;
		*(start) = patchOp; ++start;
		++blockStartIndex;
	}

	(*start).code = INVALID_OP_CODE;

	return start - *bytecode;
}

bool run(struct op_t* program)
{
	struct op_t op;
	do
	{
		op = *program++;

		int value = op.value;
		if (op.imm == 0)
		{
			value = context.regs[op.reg2];
		}

		switch (op.code)
		{
		case INP: {
			int digit = (context.input / context.div) % 10;
			if (digit == 0)
			{
				return false;
			}
			context.div /= 10;
			context.regs[op.reg1] = digit;
		} break;
		case ADD: context.regs[op.reg1] += value; break;
		case MUL: context.regs[op.reg1] *= value; break;
		case DIV: context.regs[op.reg1] /= value; break;
		case MOD: context.regs[op.reg1] %= value; break;
		case EQL: context.regs[op.reg1] = context.regs[op.reg1] == value; break;
		case PSH: {
			int sp = context.regs[S];
			value = context.regs[op.reg1];
			if (value < 1 || value > 9)
				return false;
			context.stack[sp++] = value;
			context.regs[S] = sp;
		} break;
		}

	} while (op.code < INVALID_OP_CODE);

	return true;
}

int main()
{
	struct op_t* prgProgramPatched;
	compile(data, _countof(data), &prgProgramPatched, true);

#if PART == 1
	for (int i = 9999999; i >= 1111111; --i)
#else
	for (int i = 1111111; i <= 9999999; ++i)
#endif
	{
		context.div = 1000000;
		context.input = i;
		memset(context.regs, 0, sizeof(context.regs));
		if (run(prgProgramPatched))
		{
			for (int i = 0; i < context.regs[S]; ++i)
			{
				printf("%d", context.stack[i]);
			}
			break;
		}
	}

	free(prgProgramPatched);
}