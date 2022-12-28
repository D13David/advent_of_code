#include <stdio.h>
#include <math.h>
#include <string.h>

#include "day25.h"

long long SNAFU2Dec(const char* value);

main()
{
	int i;
	long long sum = 0, tmp;
	char buffer[64], *p = buffer;

	for (i = 0; i < (sizeof(data) / sizeof(data[0])); ++i)
	{
		sum += SNAFU2Dec(data[i]);
	}

	while (sum != 0)
	{
		tmp = sum + 2;
		sum = tmp / 5;
		switch (tmp % 5)
		{
		case 0: *p++ = '='; break;
		case 1: *p++ = '-'; break;
		case 2: *p++ = '0'; break;
		case 3: *p++ = '1'; break;
		case 4: *p++ = '2'; break;
		}
	}
	for (i = p-buffer-1; i >= 0; --i)
	{
		printf("%c", buffer[i]);
	}
}

long long SNAFU2Dec(const char* value)
{
	const char* p = value + strlen(value) - 1;
	long long result = 0, pow = 1;
	for (; p >= value; --p)
	{
		switch (*p)
		{
		case '=': result = result - 2*pow; break;
		case '-': result = result - pow; break;
		case '1': result = result + pow; break;
		case '2': result = result + 2*pow; break;
		}
		pow *= 5;
	}

	return result;
}