#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define PART 2

const char* data1[] =
{
	"[[5,[[8,5],8]],[[9,3],[0,3]]]",
	"[[[8,[3,6]],[0,[1,2]]],[[[4,1],4],[7,[5,8]]]]",
	"[[[[2,0],6],[4,8]],[8,[3,0]]]",
	"[[[[8,2],[8,3]],[[0,9],5]],3]",
	"[[[[4,4],[2,3]],8],[[1,[3,8]],[8,4]]]",
	"[[[2,[1,0]],[[3,2],0]],[9,2]]",
	"[[[0,4],[[9,8],[6,6]]],3]",
	"[[[6,[6,2]],[[4,5],3]],[0,7]]",
	"[[[[2,8],4],[[1,2],[3,8]]],9]",
	"[[[3,[7,6]],[9,9]],[[8,9],[[6,2],[3,4]]]]",
	"[0,[4,[[4,1],8]]]",
	"[[[[3,3],[8,7]],[9,7]],[[7,6],4]]",
	"[[1,[[0,6],4]],[[5,[3,3]],6]]",
	"[[[0,4],7],4]",
	"[[[2,[1,7]],8],[6,[2,[8,7]]]]",
	"[[[9,7],[[2,5],[7,9]]],[1,[4,[8,6]]]]",
	"[[[[3,7],6],[[1,6],[5,4]]],[0,[6,2]]]",
	"[9,5]",
	"[[[[6,1],[4,5]],[[4,2],8]],[[5,[5,1]],[[7,3],6]]]",
	"[9,[9,[[7,4],[6,9]]]]",
	"[3,[[9,2],9]]",
	"[[[[1,7],6],[3,[9,7]]],[[6,[4,3]],[[5,6],5]]]",
	"[[[[0,6],[7,9]],[[2,8],2]],[5,[3,[4,9]]]]",
	"[0,[[[1,8],7],[9,4]]]",
	"[5,[0,[[4,5],6]]]",
	"[[[[7,9],[4,9]],[7,[7,5]]],[6,[[1,6],[8,7]]]]",
	"[[[4,[0,1]],[[9,0],[8,1]]],[[0,7],[5,[0,4]]]]",
	"[0,1]",
	"[[[[7,7],[0,7]],8],[[3,[4,2]],[6,6]]]",
	"[[[[7,8],[4,3]],[7,[7,0]]],[3,[2,3]]]",
	"[[[[6,9],[3,2]],[[4,7],2]],[[3,[7,5]],[[3,3],3]]]",
	"[7,[[[6,7],[1,3]],9]]",
	"[[[[2,9],[2,1]],[3,[9,9]]],[1,[[0,7],[2,4]]]]",
	"[[7,4],[[[0,0],5],[[2,4],5]]]",
	"[[[[2,9],8],[3,4]],[6,[[8,7],[4,3]]]]",
	"[[[8,3],0],[4,[[6,7],5]]]",
	"[[[6,[4,1]],[[1,1],[0,4]]],[[[6,2],[8,6]],[5,2]]]",
	"[9,[[[5,6],0],[[7,2],3]]]",
	"[7,[[[6,6],[1,7]],8]]",
	"[[1,[9,[6,2]]],[[4,0],[[7,7],[4,2]]]]",
	"[[[5,[5,9]],[0,[7,2]]],[[3,3],6]]",
	"[[5,[3,6]],[[0,[8,4]],[6,[5,5]]]]",
	"[[[0,5],[[8,7],[0,3]]],[[[4,1],[6,2]],[[3,2],[2,7]]]]",
	"[[[6,9],5],[[7,3],[[5,0],[2,2]]]]",
	"[[3,5],[[1,[3,4]],[2,[5,3]]]]",
	"[[9,9],[4,6]]",
	"[[[[6,4],[3,7]],[3,8]],[3,[2,[3,7]]]]",
	"[[4,[[1,1],6]],[7,[[1,1],6]]]",
	"[[[[6,4],3],9],2]",
	"[[[[8,1],3],7],[4,[9,1]]]",
	"[4,[[[7,7],6],8]]",
	"[[[7,5],[8,1]],[[6,[6,5]],[6,7]]]",
	"[[8,[3,[1,3]]],[2,[[6,1],[0,5]]]]",
	"[9,[[8,6],0]]",
	"[[8,[1,5]],[[[6,4],6],1]]",
	"[2,[[3,[4,6]],[[2,9],[6,4]]]]",
	"[[[[0,9],[2,0]],[[2,4],7]],[[[7,1],3],[7,9]]]",
	"[[[3,6],[[6,6],1]],[[[0,5],[6,8]],5]]",
	"[[[4,5],[[5,1],0]],[3,[[3,1],[2,8]]]]",
	"[[[[9,0],[7,6]],5],[6,[[0,3],1]]]",
	"[[[1,4],[5,7]],[[9,[3,8]],3]]",
	"[[[7,7],1],[[[5,0],[4,0]],8]]",
	"[[[[0,9],[0,6]],[[5,8],[7,4]]],2]",
	"[[[[0,2],1],[[4,8],0]],[4,[[8,7],[9,1]]]]",
	"[[[1,[2,0]],[[8,4],[0,0]]],5]",
	"[[[9,[8,1]],[[1,1],[4,2]]],[9,[7,[6,9]]]]",
	"[[[[0,2],[1,5]],[[9,2],[8,7]]],[[6,8],[6,0]]]",
	"[[[3,[6,7]],[[9,8],[6,9]]],[8,[[4,6],5]]]",
	"[[[9,[1,5]],[[4,8],9]],2]",
	"[[[0,[1,5]],0],0]",
	"[[[[4,1],4],[4,[7,4]]],[[[3,9],9],3]]",
	"[[[9,7],[[8,7],[0,0]]],[[[0,0],3],3]]",
	"[[9,[[2,0],6]],[[8,6],[5,4]]]",
	"[2,[6,1]]",
	"[[7,[1,[9,5]]],[[[7,8],[1,0]],[6,3]]]",
	"[[[[2,3],1],[7,3]],[[[1,5],[2,2]],[[6,3],7]]]",
	"[4,6]",
	"[[[[4,0],1],2],[[[0,5],8],[8,[0,4]]]]",
	"[[5,[7,0]],[[[4,5],[0,2]],5]]",
	"[[[5,[3,1]],[[8,4],[4,9]]],[2,[[4,8],9]]]",
	"[[[0,7],2],[[[2,5],8],[0,[5,3]]]]",
	"[[[[2,2],[8,1]],[8,[1,3]]],[6,7]]",
	"[[[9,2],[[4,8],[7,1]]],[[[5,2],7],[5,8]]]",
	"[[[2,8],[[3,6],[8,3]]],[[0,5],6]]",
	"[[[3,[7,6]],[4,[5,2]]],6]",
	"[[7,[[5,2],8]],[1,[8,[8,3]]]]",
	"[[[[8,9],7],[[1,1],0]],[[3,6],[[7,8],9]]]",
	"[[4,[[4,2],[7,9]]],[[8,9],[8,8]]]",
	"[[[5,5],[9,[0,7]]],[[[5,8],8],4]]",
	"[[8,[[4,4],[0,0]]],[[2,1],[[2,5],3]]]",
	"[[6,[[4,3],[1,6]]],0]",
	"[[[4,[1,6]],2],[[0,7],1]]",
	"[[[6,[9,9]],[4,8]],[[[1,1],9],[4,[1,7]]]]",
	"[[[[2,1],6],[[3,8],[2,2]]],[9,[7,6]]]",
	"[[0,[[1,0],9]],[8,[0,6]]]",
	"[[[8,[3,4]],[[6,7],[9,9]]],[[7,[6,8]],[[7,7],[6,8]]]]",
	"[4,[[[4,5],[4,4]],[5,[9,0]]]]",
	"[[[[8,2],7],[6,5]],2]",
	"[[9,7],[4,[[5,3],7]]]",
	"[[[[6,5],0],1],[[[5,8],[3,9]],[[9,4],[8,3]]]]"
};

const char* data2[] = { "[[1,2],[[3,4],5]]" };
const char* data3[] = { "[[[[0,7],4],[[7,8],[6,0]]],[8,1]]" };
const char* data4[] = { "[[[[1,1],[2,2]],[3,3]],[4,4]]" };
const char* data5[] = { "[[[[3,0],[5,3]],[4,4]],[5,5]]" };
const char* data6[] = { "[[[[5,0],[7,4]],[5,5]],[6,6]]" };
const char* data7[] = { "[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]" };
const char* data8[] =
{
	"[[[0,[5,8]],[[1,7],[9,6]]],[[4,[1,2]],[[1,4],2]]]",
	"[[[5,[2,8]],4],[5,[[9,9],0]]]",
	"[6,[[[6,2],[5,6]],[[7,6],[4,7]]]]",
	"[[[6,[0,7]],[0,9]],[4,[9,[9,0]]]]",
	"[[[7,[6,4]],[3,[1,3]]],[[[5,5],1],9]]",
	"[[6,[[7,3],[3,2]]],[[[3,8],[5,7]],4]]",
	"[[[[5,4],[7,7]],8],[[8,3],8]]",
	"[[9,3],[[9,9],[6,[4,9]]]]",
	"[[2,[[7,7],7]],[[5,8],[[9,3],[0,2]]]]",
	"[[[[5,2],5],[8,[3,7]]],[[5,[7,5]],[4,4]]]"
};

#define data data1

#define MIN_DEPTH_ALLOWED -5
#define MIN_VALUE_ALLOWED 9
#define MAX_BUFFER_SIZE 10000

int buffer[2][MAX_BUFFER_SIZE];
int bufferLength = 0;
int bufferIndex = 0;
int nextBufferLength = 0;
int nextBufferIndex = 0;

void beginCopyBuffer()
{
	nextBufferIndex = (bufferIndex + 1) % 2;
	nextBufferLength = 0;
}

void copyBuffer(int fromInclusive, int toExclusive)
{
	for (int i = fromInclusive; i < toExclusive; ++i)
	{
		buffer[nextBufferIndex][nextBufferLength++] = buffer[bufferIndex][i];
	}
}

void copyBufferDepthAdjust(int fromInclusive, int toExclusive, int depthOffset)
{
	for (int i = fromInclusive; i < toExclusive; ++i)
	{
		int value = buffer[bufferIndex][i];
		if (value < 0) {
			value += depthOffset;
		}
		buffer[nextBufferIndex][nextBufferLength++] = value;
	}
}

void copyBufferValue(int value)
{
	buffer[nextBufferIndex][nextBufferLength++] = value;
}

void copyBufferFromLine(const char* line, int depth)
{
	int length = strlen(line);
	for (int i = 0; i < length; ++i)
	{
		if (line[i] == '[')
		{
			++depth;
			buffer[nextBufferIndex][nextBufferLength++] = -depth;
		}
		else if (line[i] == ']')
		{
			--depth;
			buffer[nextBufferIndex][nextBufferLength++] = -depth;
		}
		else if (line[i] == ',')
		{
		}
		else
		{
			char number[2] = { line[i] };
			buffer[nextBufferIndex][nextBufferLength++] = atoi(number);
		}
	}
}

int endCopyBuffer()
{
	bufferIndex = nextBufferIndex;
	bufferLength = nextBufferLength;
}

int readBufferValue(int index)
{
	return buffer[bufferIndex][index];
}

void writeBufferValue(int index, int value)
{
	buffer[bufferIndex][index] = value;
}

void clearBuffer()
{
	bufferLength = 0;
	nextBufferLength = 0;
}

void explode(int index)
{
	// propagade left
	for (int i = index; i >= 0; --i)
	{
		if (readBufferValue(i) >= 0)
		{
			writeBufferValue(i, readBufferValue(i) + readBufferValue(index + 1));
			break;
		}
	}

	// propagade right
	for (int i = index + 4; i < bufferLength; ++i)
	{
		if (readBufferValue(i) >= 0)
		{
			writeBufferValue(i, readBufferValue(i) + readBufferValue(index + 2));
			break;
		}
	}

	beginCopyBuffer();
	copyBuffer(0, index);
	copyBufferValue(0);
	copyBuffer(index + 4, bufferLength);
	endCopyBuffer();
}

bool split()
{
	int left = -1;
	int right = -1;
	int index = 0;

	for (; index < bufferLength; ++index)
	{
		int value = readBufferValue(index);
		if (value > MIN_VALUE_ALLOWED)
		{
			left = value / 2;
			right = value - left;
			break;
		}
	}

	if (left >= 0)
	{
		int depth = readBufferValue(index - 1);
		if (depth >= 0)
			depth = readBufferValue(index - 2);

		beginCopyBuffer();
		copyBuffer(0, index);
		copyBufferValue(--depth);
		copyBufferValue(left);
		copyBufferValue(right);
		copyBufferValue(++depth);
		copyBuffer(index + 1, bufferLength);
		endCopyBuffer();
	}

	return left >= 0;
}

void reduce()
{
	do
	{
		for (int i = 0; i < bufferLength; ++i)
		{
			if (readBufferValue(i) < MIN_DEPTH_ALLOWED)
			{
				explode(i);
			}
		}
	} while (split());
}

void add(const char* line)
{
	beginCopyBuffer();
	if (bufferLength == 0)
	{
		copyBufferFromLine(line, 1);
	}
	else
	{
		copyBufferValue(-2);
		copyBufferDepthAdjust(0, bufferLength, -1);
		copyBufferFromLine(line, 2);
		copyBufferValue(-1);
	}
	endCopyBuffer();

	reduce();
}

int magnitude()
{
	bool done = true;

	do
	{
		int start = 0, end = -1;
		for (int i = 0; end == -1 && i < bufferLength; ++i)
		{
			int value = readBufferValue(i);
			if (value < 0)
			{
				if (value <= readBufferValue(start))
				{
					start = i;
				}
				else
				{
					end = i;
				}
			}
		}

		done = (end < 0);

		if (end >= 0)
		{
			beginCopyBuffer();
			copyBuffer(0, start);
			copyBufferValue(3 * readBufferValue(start + 1) + 2 * readBufferValue(end - 1));
			copyBuffer(end + 1, bufferLength);
			endCopyBuffer();
		}
	} while (!done);

	return readBufferValue(0);
}

int main()
{
#if PART == 1
	for (int i = 0; i < _countof(data); ++i)
	{
		add(data[i]);
	}

	printf("%d\n", magnitude());
#else
	int maxMagnitude = 0;

	for (int i = 0; i < _countof(data); ++i)
	{
		for (int j = 0; j < _countof(data); ++j)
		{
			if (i == j)
				continue;

			clearBuffer();
			add(data[i]);
			add(data[j]);

			int value = magnitude();

			if (value > maxMagnitude)
				maxMagnitude = value;
		}
	}

	printf("%d\n", maxMagnitude);
#endif

}