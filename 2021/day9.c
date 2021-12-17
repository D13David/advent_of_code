#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define PART 2

int data1[] =
{
    2,1,9,9,9,4,3,2,1,0,
    3,9,8,7,8,9,4,9,2,1,
    9,8,5,6,7,8,9,8,9,2,
    8,7,6,7,8,9,6,7,8,9,
    9,8,9,9,9,6,5,6,7,8
};

int data2[] =
{
    9,9,8,7,6,5,3,2,3,4,5,8,9,6,5,4,5,4,9,8,6,5,4,3,2,1,0,1,2,3,5,7,8,9,9,7,9,7,6,5,4,5,9,8,3,2,1,0,1,2,3,4,5,6,7,9,4,3,9,8,6,5,4,3,1,0,1,2,3,9,8,7,4,3,2,1,0,1,2,9,3,2,3,9,7,3,1,9,9,8,5,2,1,4,8,9,6,5,4,3,
    9,8,9,8,5,4,1,0,1,5,6,7,8,9,4,3,2,3,9,8,7,6,9,7,3,8,7,6,5,4,5,6,9,9,8,6,8,9,5,4,3,9,8,7,6,5,2,1,2,3,4,5,6,7,8,9,3,2,3,9,9,6,5,4,5,9,2,3,4,5,9,6,5,4,3,2,1,2,9,8,9,1,9,8,5,4,9,8,7,6,4,3,2,3,7,8,9,4,3,2,
    9,7,6,5,4,3,2,1,2,6,7,8,9,6,5,4,1,2,3,9,9,8,7,6,5,9,8,7,8,9,7,7,8,9,7,5,9,8,9,3,2,1,9,8,9,4,3,3,3,6,5,6,7,8,9,5,4,3,4,9,8,9,8,6,9,8,9,9,5,7,8,9,8,5,4,3,4,9,8,7,8,9,9,7,6,5,7,9,8,9,5,4,5,4,6,7,8,9,4,3,
    9,8,7,9,6,5,6,7,3,7,8,9,9,7,9,7,4,3,4,5,8,9,9,8,6,7,9,8,9,9,8,8,9,7,6,4,6,7,8,9,3,9,8,9,8,9,4,5,4,7,8,9,8,9,8,9,5,9,9,8,7,8,9,9,8,7,6,8,9,9,9,8,7,6,5,4,9,8,9,6,7,8,8,9,9,6,9,9,9,7,6,5,6,5,7,8,9,6,5,6,
    8,9,9,8,7,6,7,9,4,5,6,7,8,9,9,6,5,4,5,6,7,8,9,9,7,9,9,9,5,6,9,9,6,5,4,3,5,6,7,8,9,8,7,6,7,8,9,6,7,8,9,7,9,4,7,8,9,8,7,6,5,6,9,8,7,6,5,6,7,8,9,9,8,7,9,9,8,7,8,4,6,6,7,9,8,9,8,9,9,8,8,6,7,6,8,9,8,7,7,7,
    7,6,7,9,8,9,8,9,9,8,7,9,9,9,8,7,6,7,6,7,8,9,3,9,8,9,9,8,4,3,9,8,7,6,3,2,3,9,9,9,8,7,6,5,6,7,8,9,8,9,7,6,7,3,6,5,6,9,8,9,4,3,2,9,9,5,4,5,6,9,7,8,9,9,8,7,9,6,4,3,4,5,9,8,7,8,7,8,9,9,9,7,8,8,9,9,9,8,8,8,
    5,5,6,9,9,5,9,3,4,9,8,9,8,7,9,9,7,8,7,8,9,2,1,3,9,9,8,7,3,2,1,9,8,7,5,4,9,8,9,8,7,6,5,4,5,6,7,8,9,7,6,5,6,2,3,4,7,8,9,8,9,4,9,7,5,4,2,3,4,5,6,9,9,8,7,6,5,4,3,2,3,9,8,7,6,5,6,7,8,9,8,9,9,9,9,9,8,9,9,9,
    4,3,9,8,9,4,3,2,4,5,9,9,9,6,5,9,8,9,8,9,9,3,0,4,5,9,9,6,2,1,0,4,9,9,6,9,8,7,5,9,8,7,6,3,4,5,6,7,8,9,5,4,2,1,2,3,4,9,8,7,6,9,8,9,3,2,1,2,3,4,5,8,9,8,7,6,4,5,5,1,2,3,9,5,4,4,5,3,5,6,7,8,9,9,9,8,7,8,9,7,
    6,9,9,7,8,3,2,1,3,4,6,7,8,9,4,5,9,5,9,8,8,9,1,5,9,8,9,5,4,3,2,3,4,9,9,9,9,8,9,8,7,6,3,2,3,4,5,6,7,8,9,4,3,0,3,4,5,6,9,6,5,8,7,8,9,4,3,4,4,5,6,7,8,9,5,4,3,2,1,0,1,9,8,4,3,2,1,2,4,5,6,7,8,9,9,7,6,9,9,5,
    9,8,7,6,5,4,3,2,6,5,7,8,9,4,3,4,3,4,5,6,7,8,9,9,9,7,8,9,9,4,3,4,9,8,8,9,9,9,8,7,6,5,4,1,2,6,8,9,8,9,8,5,4,2,4,5,7,9,8,5,4,5,6,7,8,9,4,5,7,8,7,8,9,9,8,6,5,3,2,1,2,9,6,5,4,3,2,5,6,7,7,8,9,9,8,5,4,7,8,9,
    9,9,8,7,6,5,4,3,7,8,8,9,4,3,2,1,2,5,6,7,8,9,9,8,7,6,8,7,8,9,4,9,9,7,7,8,9,9,7,6,5,4,3,2,4,5,7,8,9,8,7,6,5,3,9,7,9,8,7,6,8,9,7,8,9,6,5,9,8,9,8,9,7,8,9,8,7,6,3,2,9,8,7,6,7,5,3,4,7,9,8,9,9,8,7,6,5,6,9,9,
    9,9,9,8,8,6,7,4,5,9,9,4,3,2,1,0,1,6,7,8,9,9,9,7,6,5,7,6,7,8,9,8,7,6,6,7,8,8,9,8,6,7,4,6,8,9,8,9,4,9,8,8,7,9,8,9,9,9,8,9,9,9,8,9,8,7,6,9,9,9,9,7,6,9,8,7,6,5,4,3,4,9,8,7,9,5,4,5,8,9,9,9,9,9,8,7,6,7,8,9,
    8,9,8,9,9,7,8,9,6,7,8,9,4,3,4,5,2,3,4,9,8,9,8,9,5,4,3,4,5,9,8,9,8,5,5,6,8,7,8,9,7,8,8,7,9,9,9,3,3,2,9,9,9,8,7,9,8,8,9,8,9,9,9,9,9,8,7,8,9,9,8,9,5,4,9,8,7,6,5,7,6,7,9,8,9,6,5,6,9,8,7,8,9,9,9,8,7,8,9,0,
    7,6,7,9,9,8,9,8,7,8,9,6,5,9,7,6,3,4,9,8,7,6,7,8,9,3,2,3,9,8,7,6,5,4,3,4,5,6,9,9,8,9,9,8,9,9,3,2,1,0,1,2,9,7,6,5,6,7,6,7,8,9,9,8,9,9,8,9,9,8,7,8,9,3,2,9,8,7,6,8,7,8,9,9,8,7,6,7,8,9,6,7,8,9,8,9,9,9,5,1,
    6,5,6,7,8,9,5,9,9,9,8,7,6,7,6,5,4,9,8,7,6,5,6,7,8,9,1,2,3,9,6,5,4,3,2,3,6,8,9,9,9,5,6,9,7,8,9,3,2,1,2,9,8,5,4,3,2,3,5,6,7,8,9,7,8,9,9,9,8,9,6,9,8,9,3,4,9,9,8,9,8,9,6,7,9,8,7,8,9,4,5,6,9,8,7,8,9,5,4,3,
    4,3,6,7,8,9,6,9,8,9,9,8,9,8,9,6,9,8,9,8,2,4,5,6,7,8,9,3,4,5,9,8,7,4,3,4,5,7,8,9,5,4,3,5,6,9,5,4,9,2,9,9,7,6,5,4,3,4,5,7,9,9,4,5,7,9,9,8,7,7,5,6,7,8,9,5,7,8,9,9,9,7,5,4,3,9,8,9,4,3,2,3,9,7,6,7,8,9,5,4,
    6,4,5,6,7,8,9,6,7,8,9,9,8,9,8,9,8,7,3,2,1,3,6,7,8,9,9,4,5,9,8,7,6,5,4,5,6,7,9,5,4,3,2,6,7,8,9,9,8,9,8,9,8,7,9,7,6,5,6,7,8,9,3,6,9,9,8,7,6,5,4,5,6,7,8,9,8,9,6,7,8,9,7,3,2,3,9,4,3,2,1,2,3,4,5,8,9,8,9,9,
    7,8,6,7,8,9,4,5,6,9,9,8,7,6,7,8,9,6,5,3,0,2,7,5,9,7,8,9,6,7,9,8,7,6,5,6,7,8,9,4,3,2,1,7,9,9,9,9,7,8,7,8,9,9,8,9,7,6,7,8,9,0,2,9,8,7,6,7,4,4,3,4,8,9,7,8,9,4,5,6,9,9,9,0,1,2,9,8,6,3,6,3,4,6,6,9,8,7,7,8,
    8,9,9,8,9,2,3,4,5,9,8,7,6,5,6,7,9,7,3,2,1,2,3,4,5,6,9,8,7,8,9,9,9,7,6,7,8,9,6,5,4,3,3,8,9,9,8,7,6,7,6,8,9,8,7,8,9,7,8,9,9,9,9,8,7,6,5,4,3,2,1,2,4,5,6,7,9,3,4,9,8,9,8,9,3,3,9,7,5,4,5,4,5,8,9,7,5,6,6,7,
    9,7,6,9,2,1,2,5,9,8,7,6,5,4,5,9,8,9,5,4,6,3,4,5,6,7,8,9,8,9,4,3,9,8,7,8,9,8,7,7,5,4,9,9,9,8,7,6,5,6,5,6,3,4,6,7,8,9,9,9,8,7,6,9,8,7,6,5,4,5,6,3,5,6,8,8,9,4,9,8,7,9,7,9,9,4,9,8,6,5,6,8,6,7,8,9,4,3,5,6,
    9,8,5,4,3,2,4,9,8,7,6,5,4,3,4,6,7,8,9,6,5,4,5,7,7,8,9,9,9,4,3,2,3,9,8,9,9,9,8,8,6,9,8,9,9,9,8,5,4,3,4,1,2,4,7,8,9,8,9,8,7,6,5,3,9,8,7,6,7,8,9,8,6,7,9,9,1,9,8,7,6,5,6,7,8,9,9,9,9,8,7,9,7,8,9,6,5,4,5,7,
    9,9,8,5,4,5,9,8,7,6,5,3,2,2,3,5,6,7,8,9,6,8,6,8,8,9,8,7,6,5,2,1,2,4,9,8,9,9,9,8,7,9,6,5,9,8,7,6,3,2,1,0,1,2,3,5,6,7,8,9,7,6,3,2,5,9,8,7,8,9,9,8,7,8,9,1,0,1,9,6,5,4,5,6,9,9,9,8,7,9,8,9,8,9,9,7,6,7,6,8,
    9,8,7,6,5,9,8,7,5,4,3,2,1,0,1,4,5,6,7,9,9,9,7,9,9,9,9,9,8,7,3,0,1,5,6,7,8,9,9,9,9,8,7,6,7,9,8,7,4,3,3,1,2,3,4,8,9,8,9,9,8,5,4,3,4,6,9,8,9,3,4,9,8,9,8,9,1,9,8,5,4,3,4,5,6,9,8,9,6,5,9,4,9,7,8,9,9,8,7,9,
    4,9,8,7,9,9,9,8,6,5,4,3,2,3,2,3,4,5,6,7,8,9,8,9,9,9,9,8,7,5,4,1,2,3,7,8,9,6,8,7,7,9,8,7,9,8,7,6,5,7,6,5,3,4,5,7,8,9,2,3,9,7,5,4,5,6,7,9,1,2,9,8,9,6,7,8,9,7,6,4,3,2,3,4,5,6,7,8,9,4,3,2,3,6,9,1,0,9,8,9,
    3,9,9,9,9,9,8,9,7,8,5,4,3,4,7,6,5,6,7,8,9,6,9,7,8,8,9,9,8,7,5,2,3,4,8,9,6,5,4,5,6,7,9,9,6,9,8,9,6,8,8,9,6,5,6,8,9,0,1,9,8,7,6,5,6,7,8,9,0,9,8,7,6,5,4,9,8,7,6,3,2,1,2,3,4,5,6,7,8,9,4,3,4,5,8,9,9,8,9,4,
    9,8,9,9,9,8,7,9,8,7,6,5,4,5,8,7,6,7,8,9,6,5,3,5,6,7,8,9,9,8,6,3,4,6,7,8,9,6,3,9,8,8,9,3,4,5,9,8,7,9,9,2,9,8,7,9,9,9,3,4,9,9,8,9,9,9,9,9,9,9,9,9,5,4,3,4,9,6,5,4,3,0,9,9,9,6,9,8,9,9,5,4,5,6,7,8,9,7,6,3,
    8,7,8,9,9,9,5,3,9,8,7,6,5,6,9,8,7,8,9,6,4,3,2,3,5,8,9,4,3,9,8,9,5,6,9,9,8,7,9,8,9,9,9,2,3,9,8,9,9,8,9,3,9,9,8,9,7,8,9,6,9,9,9,9,8,9,8,9,8,9,9,8,4,3,2,9,8,7,6,9,9,9,8,7,8,9,8,9,9,7,6,5,6,8,9,9,7,6,5,4,
    7,6,7,9,8,7,6,2,1,9,8,7,6,7,8,9,8,9,6,5,4,2,1,2,9,9,0,1,2,3,9,8,9,9,8,8,9,8,9,7,7,7,8,9,9,8,7,6,5,7,8,9,8,7,9,5,6,9,9,9,8,9,9,8,7,8,7,8,7,8,9,6,5,5,1,0,9,9,9,8,7,6,5,6,7,6,7,8,9,8,7,8,7,9,9,9,8,7,9,5,
    6,5,6,9,9,9,7,9,0,1,9,8,9,8,9,1,9,8,7,8,4,3,4,5,8,9,1,3,4,9,8,7,8,8,7,7,8,9,7,6,6,6,7,8,9,7,6,5,4,6,7,8,9,6,5,4,5,6,9,8,7,9,9,7,6,7,6,5,6,7,8,9,4,3,2,3,9,8,7,9,5,5,4,7,6,5,6,7,8,9,8,9,8,9,9,8,9,9,8,9,
    5,4,9,8,7,8,9,8,9,2,3,9,9,9,3,2,3,9,8,9,5,4,5,6,7,8,9,4,9,8,7,6,5,4,5,6,7,8,9,5,4,5,6,7,8,9,6,4,2,5,6,7,8,9,4,2,3,5,6,9,5,9,8,7,5,4,3,4,7,8,9,9,9,4,9,9,8,7,6,5,4,5,3,1,3,4,5,6,7,8,9,8,9,9,8,7,6,5,6,7,
    6,9,8,7,6,7,8,7,8,9,9,9,9,5,4,3,4,5,9,9,8,7,6,7,8,9,5,9,8,7,6,5,4,3,6,7,9,9,3,2,3,7,8,9,9,6,5,4,3,4,5,6,9,6,5,1,2,3,9,8,4,3,9,9,8,6,4,5,6,9,9,9,8,9,8,9,9,8,5,4,3,2,1,0,1,2,3,9,8,9,8,7,9,8,7,6,5,4,5,6,
    9,8,7,6,5,4,6,6,7,9,8,9,8,9,5,4,5,6,7,9,9,9,7,8,9,5,4,6,9,8,7,6,2,1,7,6,7,8,9,1,5,6,7,7,8,9,6,5,4,5,8,7,8,9,3,2,3,9,9,7,3,2,9,8,7,6,5,6,7,8,9,8,7,8,7,9,8,7,6,5,4,3,2,1,2,3,4,5,9,9,5,6,9,7,6,5,4,3,6,7,
    9,9,6,5,4,3,4,5,6,9,7,6,7,8,9,5,9,7,8,9,9,9,8,9,3,2,3,4,5,9,8,8,3,2,3,4,8,9,3,2,3,4,5,6,9,8,7,6,5,6,9,8,9,5,4,3,9,8,7,6,4,5,6,9,9,7,6,7,8,9,6,5,6,5,6,8,9,8,7,6,5,4,3,2,3,4,7,6,7,8,9,9,8,7,7,4,3,2,5,6,
    8,9,5,4,3,2,3,6,9,8,9,5,6,7,8,9,8,9,9,9,9,8,9,4,2,1,9,5,6,7,9,9,5,3,5,6,7,8,9,3,4,7,8,9,9,9,8,7,6,7,9,9,9,6,5,4,9,9,8,6,5,6,7,8,9,8,9,8,9,6,5,4,3,4,5,9,9,9,9,8,6,6,4,5,5,6,7,8,9,9,9,9,7,6,5,5,1,0,4,5,
    6,5,6,1,0,1,2,9,8,7,5,4,5,6,9,8,7,8,8,9,8,7,8,9,3,9,8,9,9,9,8,7,6,9,8,7,8,9,8,7,5,6,7,8,9,6,9,8,7,8,9,9,8,9,6,9,8,9,9,8,7,8,8,9,2,9,8,9,8,5,4,3,2,1,9,8,7,5,4,9,8,6,5,6,6,7,8,9,6,7,8,9,8,5,4,3,2,1,3,6,
    7,4,3,2,1,2,3,4,9,8,6,9,9,9,8,7,6,6,7,8,9,6,7,8,9,8,7,8,8,9,9,9,8,9,9,8,9,9,8,7,6,7,9,9,7,5,6,9,9,9,8,9,6,8,9,6,7,8,9,9,8,9,9,4,3,6,7,9,6,5,3,2,1,0,9,6,5,6,3,4,9,7,6,7,8,9,9,4,5,6,7,9,8,6,5,4,4,3,5,7,
    6,5,4,3,4,3,4,6,7,9,9,8,7,8,9,3,4,5,9,9,4,5,6,9,8,7,6,6,7,8,9,9,9,4,5,9,7,8,9,9,7,8,9,6,5,4,5,9,9,8,7,6,5,7,5,5,6,9,8,9,9,7,6,5,4,5,9,8,7,6,4,3,2,9,8,5,4,3,2,3,9,8,9,8,9,3,2,3,4,5,6,9,8,7,6,5,5,4,5,6,
    7,6,5,4,5,4,5,6,8,9,8,7,6,7,8,9,9,6,7,8,9,7,9,8,7,6,5,5,6,7,9,9,1,3,4,5,6,7,8,9,8,9,8,7,6,5,9,8,9,9,7,5,4,3,3,4,5,6,7,8,9,8,7,6,7,6,7,9,8,9,9,4,9,8,7,4,3,2,1,0,1,9,9,9,8,9,1,0,1,2,7,8,9,8,7,6,7,6,6,7,
    8,9,6,5,6,5,6,7,9,8,7,6,5,6,6,7,8,9,8,9,9,8,9,8,6,5,4,3,4,8,9,8,9,4,7,6,8,9,9,8,9,9,9,8,9,9,8,7,9,8,7,4,3,2,1,3,8,7,8,9,9,9,8,9,8,9,8,9,9,8,8,9,9,8,6,5,4,3,2,1,2,5,9,8,7,8,9,1,2,3,8,9,8,9,8,9,8,7,9,8,
    9,8,7,8,9,6,9,8,9,9,8,7,4,3,5,6,7,8,9,9,9,9,9,9,7,4,3,2,3,5,6,7,8,9,8,9,9,5,6,7,8,9,9,9,9,9,8,6,7,9,6,5,4,3,4,4,5,8,9,8,9,9,9,9,9,9,9,9,8,7,6,7,8,9,7,6,7,4,3,4,3,4,9,7,6,9,8,9,3,4,9,8,7,6,9,9,9,8,9,9,
    4,9,8,9,8,7,8,9,9,8,5,4,3,2,3,5,6,7,8,9,8,9,8,5,4,3,2,1,2,4,7,8,9,5,9,1,2,4,5,6,7,8,9,9,9,8,7,5,9,8,7,6,5,4,5,7,8,9,6,7,8,9,4,9,8,9,9,9,9,8,7,8,9,9,8,7,8,5,4,5,8,9,8,6,5,8,7,8,9,9,8,7,8,5,6,7,9,9,7,8,
    3,4,9,7,9,8,9,9,8,7,6,5,4,1,4,6,7,8,9,6,7,9,7,6,5,4,3,2,3,4,6,9,5,4,3,2,3,4,5,7,9,9,1,9,8,7,6,4,3,9,8,7,8,5,6,8,9,4,5,8,9,4,3,9,7,8,9,7,6,9,8,9,3,4,9,8,7,6,7,6,7,9,7,6,4,5,6,7,9,8,7,6,5,4,5,9,8,7,6,7,
    2,3,5,6,7,9,9,9,9,8,7,6,3,2,5,9,8,9,5,4,3,4,9,9,6,5,6,6,4,5,9,8,9,9,4,9,6,5,6,7,8,9,0,9,8,7,7,3,2,2,9,8,9,9,7,8,9,3,4,9,9,9,9,8,6,9,8,9,5,4,9,0,2,9,9,9,8,9,8,7,9,8,9,4,3,4,5,8,9,7,6,5,4,3,9,8,7,6,5,6,
    1,3,4,5,9,9,8,7,5,9,9,9,8,7,6,8,9,9,9,3,2,3,9,8,7,8,7,8,6,9,8,7,9,8,9,8,9,6,9,8,9,9,9,8,9,6,5,2,1,0,1,9,4,9,8,9,0,2,5,7,8,8,9,6,5,8,7,8,9,3,2,1,9,8,9,9,9,9,9,9,8,7,6,5,4,5,6,9,9,9,8,6,5,1,0,9,8,9,4,5,
    2,3,4,9,8,8,7,6,4,6,7,8,9,8,7,8,9,9,8,9,0,9,9,9,8,9,8,9,7,8,9,6,5,7,4,7,8,9,8,9,2,9,8,7,6,5,4,3,2,3,2,9,3,9,9,3,1,2,4,5,6,7,8,9,4,7,6,7,8,9,3,9,9,7,8,9,9,9,9,8,9,8,7,6,5,8,7,8,9,7,9,7,3,2,1,2,9,8,5,7,
    3,4,9,8,7,6,5,4,3,4,8,9,9,9,8,9,9,8,7,8,9,8,9,9,9,9,9,9,8,9,6,5,4,5,3,6,5,6,7,9,1,0,9,8,7,6,5,4,3,4,9,8,9,8,9,4,2,3,9,6,9,8,9,3,3,4,5,9,9,5,9,8,7,6,7,8,9,8,9,7,6,9,8,7,6,9,8,9,5,6,9,8,4,3,5,9,8,7,6,7,
    4,5,9,9,8,9,4,3,2,3,9,8,7,8,9,9,8,7,6,6,6,7,8,9,9,8,9,9,9,8,7,6,2,1,2,3,4,5,6,8,9,1,4,9,9,7,6,5,6,9,8,7,8,7,8,9,4,4,8,7,8,9,3,2,2,3,9,8,9,4,5,9,8,5,4,7,5,6,8,9,7,8,9,8,9,8,9,5,4,7,9,9,5,5,6,7,9,8,7,8,
    5,6,8,9,9,8,9,2,1,0,1,9,6,9,9,8,7,6,5,4,5,6,7,8,9,7,8,9,8,7,6,2,1,0,1,4,5,6,7,9,3,2,3,4,9,8,9,7,9,7,6,6,5,6,7,8,9,5,9,8,9,2,1,0,1,9,8,7,9,5,9,8,7,8,3,2,4,5,6,8,9,9,9,9,8,7,9,4,3,9,8,7,6,6,7,8,9,9,8,9,
    6,7,9,9,8,7,8,9,2,3,9,6,5,4,4,9,8,8,7,5,6,7,8,9,5,6,9,8,7,6,5,4,2,1,2,3,4,7,8,9,4,5,9,9,8,9,8,9,8,7,5,3,4,5,6,7,8,9,9,9,4,3,4,5,9,8,9,6,8,9,9,7,6,5,4,1,3,6,8,9,5,4,9,8,9,6,8,9,2,3,9,8,7,7,8,9,9,9,9,9,
    7,8,9,9,7,6,9,9,9,9,8,7,4,3,3,5,9,9,8,7,8,9,9,8,9,8,9,9,8,7,6,5,3,2,3,6,5,6,7,8,9,9,8,8,7,6,7,8,9,8,6,6,5,6,7,8,9,9,9,8,5,4,5,9,8,7,8,5,9,9,9,8,7,4,3,0,2,6,7,8,9,3,9,7,6,5,7,8,9,9,9,9,8,8,9,9,8,9,8,9,
    8,9,9,8,9,5,8,9,8,9,9,1,0,1,2,6,9,9,9,8,9,5,6,7,8,9,1,6,9,9,8,6,4,5,4,6,6,9,8,9,8,9,7,6,6,5,7,8,9,8,7,7,6,8,9,9,3,9,8,7,6,5,9,8,7,6,6,4,6,9,8,9,8,5,2,1,2,5,6,7,9,9,8,6,5,4,5,6,7,8,9,7,9,9,9,8,7,8,7,9,
    9,9,8,7,8,4,7,7,6,8,9,2,1,2,3,7,8,9,9,9,3,4,6,8,9,1,0,5,6,7,9,6,5,6,5,6,7,8,9,8,7,8,6,5,4,4,5,9,8,9,9,9,9,9,4,3,2,4,9,8,7,9,8,7,6,5,4,3,4,9,7,6,5,4,3,2,3,4,5,9,8,7,6,7,4,3,4,7,8,8,9,6,5,9,8,7,6,5,6,7,
    9,8,7,6,4,2,6,4,5,7,8,9,2,3,5,7,9,9,8,9,2,5,6,9,3,2,2,3,9,9,8,7,6,9,7,7,9,9,8,7,6,5,4,3,2,3,9,8,7,8,8,7,8,8,9,2,1,2,9,9,8,9,9,8,7,4,3,2,3,4,9,7,8,5,4,5,4,6,9,8,7,6,5,4,4,2,3,5,6,7,8,9,9,8,7,6,5,4,5,8,
    8,7,6,5,2,1,2,3,4,6,8,9,5,4,6,8,9,8,7,9,9,8,7,8,9,3,3,9,8,9,9,8,7,8,9,8,9,8,7,6,5,4,3,1,0,5,9,8,6,4,5,5,6,7,8,9,2,9,8,9,9,9,9,9,8,3,2,1,2,3,9,8,7,6,7,6,5,6,9,9,9,8,4,3,2,1,2,3,7,8,9,9,8,9,8,9,6,3,4,5,
    9,8,9,3,1,0,1,2,8,7,8,9,6,7,7,8,9,5,6,7,8,9,8,9,5,4,9,8,7,9,9,9,8,9,2,9,4,9,8,7,6,5,4,2,1,9,8,7,5,3,3,4,5,9,9,9,9,8,7,9,8,9,8,7,6,5,4,0,1,6,8,9,8,9,8,7,9,7,8,9,8,7,6,5,4,2,3,4,5,9,9,8,6,8,9,8,7,4,5,6,
    7,6,5,4,2,4,2,3,9,8,9,6,9,8,8,9,5,4,5,6,7,8,9,7,6,9,8,7,6,8,9,9,9,0,1,2,3,4,9,9,8,6,4,3,2,9,8,8,3,2,2,3,6,7,8,9,9,8,6,5,7,9,9,8,7,6,2,1,4,5,6,7,9,3,9,8,9,8,9,3,9,8,7,6,6,3,4,5,6,7,8,9,5,6,8,9,7,6,7,8,
    8,7,6,5,3,5,7,8,9,9,9,5,4,9,9,5,4,3,4,5,6,9,9,8,9,8,7,6,5,7,8,9,2,1,9,3,4,9,8,7,9,8,6,5,9,8,7,6,1,0,1,9,9,9,9,9,9,9,7,3,6,7,9,9,7,6,3,2,3,4,7,8,9,2,3,9,7,9,9,2,1,9,8,7,5,4,5,8,7,8,9,3,4,5,9,9,9,7,8,9,
    9,8,7,6,4,5,9,9,8,7,8,9,9,8,9,4,3,2,3,6,7,8,9,9,8,8,7,5,4,6,7,8,9,9,8,9,5,9,7,6,7,9,7,9,8,7,6,5,2,1,2,8,7,8,9,9,8,9,9,4,5,6,8,9,6,5,4,7,5,6,8,9,4,3,4,5,6,7,8,9,9,8,9,8,6,5,6,7,8,9,1,2,3,9,8,9,9,8,9,9,
    9,9,8,7,6,9,9,8,9,6,7,9,8,7,8,9,4,3,4,7,8,9,8,9,7,6,5,4,3,2,3,4,5,6,7,8,9,9,8,5,6,9,8,9,7,6,5,4,3,2,3,4,5,6,7,9,6,8,8,9,6,7,9,8,7,6,5,8,9,7,8,9,5,6,5,6,7,9,9,9,9,7,8,9,7,6,7,8,9,1,0,1,9,8,7,7,6,9,9,9,
    8,9,9,8,9,8,8,7,6,5,6,6,7,6,7,8,9,4,5,8,9,6,7,8,9,8,7,6,2,1,2,3,4,5,6,9,9,9,9,6,7,8,9,9,8,7,6,5,4,3,4,5,6,7,8,9,5,9,7,8,9,9,8,9,8,7,8,9,9,8,9,7,6,7,6,7,8,9,9,9,7,6,7,9,8,9,8,9,3,2,1,9,8,7,6,6,5,6,7,8,
    7,9,9,9,8,7,6,5,5,4,3,5,4,5,8,8,9,9,6,9,4,5,6,7,9,8,7,7,1,0,3,4,5,6,7,8,9,8,6,9,8,9,9,8,9,8,7,6,5,4,5,8,7,8,9,3,4,5,6,7,8,9,6,9,9,8,9,3,2,9,9,8,7,8,7,8,9,9,9,8,6,5,6,5,9,7,9,6,4,9,9,8,9,5,4,3,4,7,8,9,
    6,7,8,9,9,8,7,4,3,2,1,4,3,4,5,6,7,8,9,4,3,9,9,9,8,7,6,5,2,1,3,4,6,7,8,9,9,9,5,3,9,9,8,7,6,9,8,9,6,5,6,9,9,9,4,2,3,4,5,6,9,6,5,8,9,9,1,0,1,2,9,9,8,9,8,9,9,9,8,7,6,4,5,4,6,6,7,9,9,8,7,6,5,4,3,2,3,8,9,0,
    5,6,7,9,8,9,6,5,4,1,0,1,2,3,4,5,7,9,9,5,9,8,7,8,9,8,7,4,3,2,7,8,7,8,9,6,9,8,9,2,9,8,7,6,5,4,9,8,7,6,7,8,9,9,6,5,4,5,6,7,8,9,6,7,9,8,9,1,2,9,8,7,9,0,9,9,8,7,6,5,4,3,2,3,4,5,6,7,8,9,9,7,9,5,4,3,4,8,9,1,
    4,5,9,8,7,6,5,4,3,2,1,2,3,5,6,9,8,9,8,9,8,7,6,7,8,9,8,5,4,5,6,7,8,9,4,5,9,7,8,9,8,9,8,7,4,3,4,9,8,7,8,9,9,8,9,7,5,6,7,8,9,8,7,9,8,7,8,9,9,8,7,6,5,1,4,6,9,9,8,7,3,2,1,2,5,6,9,8,9,0,1,9,8,9,5,4,5,7,8,9,
    3,7,5,9,9,8,6,5,4,3,2,3,4,6,7,8,9,8,7,6,5,6,5,8,9,8,7,6,7,6,9,8,9,8,6,9,8,6,5,7,7,8,9,9,9,2,1,0,9,8,9,9,9,7,8,9,9,7,8,9,4,9,9,8,7,6,7,8,9,9,9,4,3,2,3,7,9,8,4,3,2,1,0,1,6,9,8,9,9,9,2,9,7,8,9,5,6,8,9,7,
    2,3,4,9,8,9,8,7,5,7,6,5,5,9,8,9,8,9,8,7,4,3,4,5,6,9,8,9,8,9,9,9,9,9,9,9,8,7,4,5,6,7,8,9,8,9,2,3,4,9,9,8,8,6,8,7,8,9,9,2,3,4,9,9,6,5,6,7,9,8,8,9,5,3,4,9,8,7,5,4,3,2,2,3,4,6,7,8,9,8,9,8,6,7,8,9,7,8,9,6,
    3,4,9,8,7,6,9,8,9,8,7,6,7,9,9,5,6,7,9,7,5,4,6,8,7,8,9,4,9,9,9,8,9,9,8,9,9,9,8,7,7,8,9,8,7,8,9,7,6,9,8,7,6,5,4,6,8,9,9,3,4,9,8,7,5,4,3,2,3,6,7,8,9,7,6,7,9,7,6,5,4,3,3,4,5,6,8,9,8,7,6,5,4,6,7,8,9,9,6,5,
    5,9,5,7,6,5,6,9,9,9,8,9,8,9,9,4,8,8,9,8,9,8,7,9,8,9,4,3,4,9,9,7,8,9,7,8,9,9,9,8,8,9,8,7,6,9,8,9,7,9,9,8,7,4,3,4,7,6,8,9,9,8,7,6,4,3,2,1,2,5,6,9,8,9,7,8,9,8,9,9,5,4,4,9,6,8,9,8,7,6,5,4,3,5,7,8,9,9,5,4,
    9,8,4,3,5,4,5,9,8,9,9,1,9,9,8,9,9,9,8,9,8,9,8,9,9,9,5,4,9,8,7,6,7,9,6,7,8,9,6,9,9,8,7,6,5,8,7,8,9,8,7,6,5,3,2,5,4,5,8,9,9,9,7,6,5,2,1,0,3,4,5,6,7,8,9,9,9,9,9,7,9,5,9,8,7,9,9,9,8,7,6,3,2,3,5,6,7,8,9,3,
    8,7,3,2,1,3,5,6,7,8,9,0,9,8,7,8,9,6,7,8,7,9,9,9,9,8,9,9,9,9,5,5,6,4,5,9,9,3,5,7,8,9,7,6,4,5,6,7,9,9,8,7,6,2,1,2,3,6,7,9,8,7,6,5,4,3,2,1,4,5,6,7,8,9,7,8,9,8,8,6,8,9,9,9,9,8,9,9,9,4,3,2,1,3,6,7,9,9,5,4,
    7,6,4,3,0,1,4,7,8,9,9,9,8,7,6,5,4,5,6,5,6,8,9,9,8,7,8,8,9,9,4,3,2,3,7,8,8,9,6,9,9,1,9,8,7,6,7,9,8,7,6,8,7,3,0,3,4,5,6,7,9,8,9,6,5,4,3,2,6,7,9,8,9,5,6,9,8,7,6,5,7,8,9,9,8,7,9,8,6,5,4,3,2,3,7,8,9,8,7,5,
    8,6,5,4,1,2,3,8,9,8,9,9,9,6,5,4,3,4,5,4,5,7,8,9,7,6,5,6,7,8,9,5,1,5,6,7,7,8,9,6,3,2,3,9,8,7,8,9,8,6,5,4,3,2,1,6,5,6,7,8,9,9,8,7,6,5,5,3,5,8,9,9,3,4,5,9,8,7,5,4,6,7,9,8,7,6,9,8,7,6,5,4,3,4,8,9,2,9,9,6,
    8,7,6,6,2,3,4,5,6,7,8,9,8,7,4,3,2,1,2,3,4,5,7,8,9,5,3,4,9,9,4,3,2,3,4,5,6,9,6,5,4,3,4,5,9,8,9,8,9,7,6,5,4,4,2,7,6,7,8,9,5,6,9,8,7,6,7,4,6,7,8,9,2,3,9,8,7,6,4,3,4,5,6,9,6,5,4,9,8,7,6,5,4,5,9,9,3,9,8,9,
    9,8,7,4,3,4,5,6,7,8,9,9,9,8,3,2,1,0,1,2,3,4,6,7,9,4,2,3,9,8,9,4,3,4,6,9,9,7,9,9,5,6,5,9,8,9,6,7,9,8,7,7,6,5,3,4,5,8,9,5,4,3,4,9,8,7,8,8,7,8,9,2,1,9,8,7,6,5,3,2,3,4,9,8,6,5,3,9,9,8,7,6,5,6,7,8,9,8,7,8,
    9,9,6,5,6,5,7,8,9,9,2,9,8,7,4,3,2,1,2,3,4,5,8,9,4,2,1,2,8,7,8,9,4,5,9,8,7,6,7,8,9,7,6,9,7,6,5,4,7,9,8,9,7,6,5,6,6,9,7,6,5,6,8,9,9,8,9,9,8,9,4,3,9,8,7,6,5,4,3,1,2,3,4,9,7,6,9,8,9,9,8,7,6,7,8,9,9,7,6,4,
    9,8,7,6,7,9,8,9,2,1,0,1,9,6,5,4,3,2,3,4,5,6,9,8,2,1,0,4,5,6,7,8,9,9,8,6,6,5,6,7,8,9,9,8,6,7,4,3,5,6,9,9,8,7,8,8,7,8,9,9,8,7,9,9,9,9,7,6,9,9,5,4,5,9,9,8,6,5,3,2,3,4,5,9,8,9,8,7,8,9,9,8,8,9,9,9,8,9,4,3,
    3,9,8,9,8,9,9,8,9,2,1,9,8,7,6,7,4,3,4,5,6,9,8,7,7,3,2,3,4,5,6,9,9,8,7,5,3,4,6,7,9,9,7,6,5,4,5,2,6,7,8,9,9,8,9,9,8,9,2,1,9,9,8,9,8,7,6,5,7,8,9,7,6,7,8,9,8,5,4,4,4,7,6,7,9,9,9,6,8,6,7,9,9,5,3,8,7,8,9,1,
    1,2,9,8,9,5,6,7,8,9,2,9,9,8,7,8,5,6,5,6,7,8,9,6,5,4,3,4,5,6,7,8,9,7,5,4,2,3,4,6,7,8,9,6,4,3,2,1,4,5,6,7,9,9,9,8,9,4,3,2,9,8,7,8,9,6,4,3,4,7,8,9,7,8,9,9,9,6,5,5,5,7,7,9,8,7,6,5,4,5,6,8,9,4,2,1,6,7,8,9,
    0,9,8,7,6,4,5,8,9,8,9,8,9,9,8,9,6,7,8,7,8,9,8,7,6,5,4,5,8,7,8,9,6,5,3,2,1,5,7,8,9,9,8,7,5,9,3,2,3,4,5,6,9,9,9,7,6,5,4,9,8,7,6,7,8,9,4,2,5,6,7,9,8,9,4,9,8,7,6,6,7,8,9,8,7,6,5,4,3,4,5,8,9,2,1,0,5,8,9,9,
    2,6,9,8,7,6,6,9,8,7,6,7,8,9,9,7,9,8,9,8,9,8,9,8,7,8,5,6,9,8,9,9,5,4,3,2,0,7,8,9,8,6,9,8,9,8,9,3,7,5,9,9,8,7,8,9,7,8,9,8,7,8,5,6,9,4,3,1,4,5,7,8,9,4,3,2,9,8,8,9,8,9,9,9,8,7,4,3,2,3,6,7,8,9,3,2,4,6,7,8,
    3,4,9,9,9,8,9,8,9,8,5,9,8,9,6,5,3,9,7,9,9,7,6,9,8,9,6,7,8,9,8,7,6,5,4,3,4,8,9,9,7,5,4,9,9,7,9,9,9,9,8,7,5,6,7,8,9,9,8,7,6,6,4,5,8,9,4,2,3,5,6,9,9,9,2,1,2,9,9,0,9,6,9,9,9,9,8,4,3,4,5,6,7,9,4,3,4,5,6,7,
    9,9,8,8,9,9,8,7,6,5,4,6,7,8,9,3,2,3,6,7,8,9,5,7,9,9,8,9,9,9,9,8,8,7,5,4,5,6,7,8,9,7,5,9,8,6,8,7,8,9,7,6,4,5,8,9,9,8,7,6,5,4,3,4,6,8,9,3,4,6,7,8,9,8,9,0,9,3,2,1,2,5,7,8,9,9,6,5,4,5,6,7,9,6,5,4,5,6,7,8,
    8,9,7,6,8,9,9,7,5,4,3,5,9,9,9,2,1,2,5,6,7,9,4,5,6,7,9,9,9,9,9,9,9,9,6,9,8,7,8,9,8,7,6,7,9,5,4,6,7,8,9,1,3,6,7,9,9,9,9,8,6,3,2,3,4,7,8,9,5,6,8,9,6,7,9,9,8,4,3,2,3,4,6,9,9,8,7,8,7,6,7,8,9,9,6,9,6,8,9,9,
    7,8,9,5,7,8,9,9,7,3,2,9,8,9,8,9,0,1,4,5,6,8,9,6,7,8,9,8,9,8,9,4,3,9,8,9,9,9,9,4,9,8,7,9,8,4,3,5,6,9,1,0,1,7,9,8,9,8,7,9,7,2,1,2,6,6,7,8,9,7,9,7,5,6,8,9,7,5,4,3,4,8,7,8,9,9,8,9,8,7,8,9,9,8,7,8,9,9,9,9,
    6,4,3,4,8,9,0,9,8,9,9,8,7,8,7,8,9,2,3,6,9,9,8,7,8,9,8,7,6,7,8,9,2,1,9,9,9,8,9,3,4,9,9,8,7,8,2,6,8,8,9,9,2,9,8,7,8,9,5,9,8,6,0,1,4,5,7,8,9,8,9,5,4,5,7,9,7,6,5,6,7,8,8,9,5,6,9,9,9,8,9,3,4,9,8,9,9,6,7,8,
    5,4,2,3,9,2,1,2,9,8,7,5,6,8,6,7,8,9,5,7,8,9,9,9,9,8,9,6,5,6,9,8,9,0,1,9,8,7,8,9,9,8,9,8,6,2,1,5,6,7,8,8,9,6,5,6,7,8,9,8,7,5,4,2,3,5,6,7,8,9,3,4,3,4,6,7,9,9,9,7,8,9,9,3,4,9,8,9,9,9,3,2,1,0,9,9,8,5,6,9,
    8,7,3,7,8,9,3,9,8,9,9,4,3,4,5,8,9,7,6,7,9,9,9,9,8,7,6,5,4,7,6,7,8,9,9,8,7,6,7,9,8,7,6,5,4,5,0,3,4,5,6,7,8,9,4,5,8,9,9,9,9,7,5,3,4,7,8,9,9,3,2,1,2,9,7,9,8,7,8,9,9,2,1,2,9,8,7,8,9,9,4,9,2,1,9,8,7,6,7,8,
    9,6,5,6,7,9,4,9,7,9,8,9,9,5,6,9,9,8,7,9,9,9,8,9,9,6,5,4,3,4,5,6,7,9,8,7,6,5,4,3,9,8,7,6,3,2,1,2,3,4,7,8,9,4,3,4,9,9,8,9,8,7,6,4,5,8,9,4,3,2,1,0,9,8,9,8,7,6,9,9,9,4,9,3,9,7,6,9,7,8,9,8,9,2,9,9,8,9,8,9,
    8,7,6,7,9,9,9,8,6,8,7,6,7,9,8,9,7,9,9,8,9,8,6,9,8,7,6,5,4,7,6,7,8,9,9,9,9,4,3,2,4,9,9,8,4,3,2,3,4,5,6,9,6,5,4,9,8,6,7,8,9,8,7,8,9,9,7,6,4,3,4,9,8,7,8,9,3,5,6,9,8,9,8,9,8,6,5,4,6,9,8,7,8,9,8,9,9,1,9,4,
    9,8,7,9,8,9,8,6,5,7,6,5,7,8,9,5,6,9,8,7,9,5,4,3,9,8,7,6,9,8,7,8,9,9,9,8,7,6,5,4,6,7,8,9,5,4,5,4,5,6,7,8,9,9,9,8,7,5,6,8,8,9,8,9,0,1,9,7,5,9,5,6,9,6,5,3,2,3,9,8,7,6,7,8,9,5,4,3,9,8,7,6,9,8,7,8,9,0,1,2,
    6,9,9,8,7,7,5,4,3,2,3,4,8,8,9,4,2,3,9,6,7,9,9,2,1,9,9,7,8,9,8,9,7,8,9,9,8,7,6,7,9,8,9,8,7,6,7,8,9,7,8,9,7,8,9,6,5,4,5,6,7,8,9,9,9,9,8,9,6,7,8,9,8,7,6,4,6,9,9,8,6,5,6,7,8,9,5,2,9,8,6,5,6,7,6,7,8,9,2,9,
    5,9,8,7,6,5,4,3,2,1,2,5,6,7,8,9,1,9,7,5,9,8,7,9,9,9,9,8,9,2,9,8,6,7,8,9,9,8,9,8,9,9,9,9,8,7,8,9,9,8,9,7,6,9,8,9,7,3,4,5,6,7,8,9,7,8,7,9,7,8,9,7,9,9,7,8,9,8,9,9,7,6,7,8,9,7,6,9,8,7,8,4,5,4,5,6,7,8,9,8,
    4,5,9,8,7,6,3,2,1,0,3,6,8,8,9,8,9,8,6,4,8,7,6,7,8,9,9,9,2,1,3,4,5,6,7,8,9,9,4,9,9,8,9,9,9,8,9,2,1,9,5,4,5,6,7,8,9,2,5,6,7,9,9,8,6,5,6,8,9,9,7,5,4,9,8,9,9,7,8,9,8,7,8,9,9,8,7,9,7,6,4,3,2,3,6,7,8,9,8,6,
    3,4,5,9,8,7,5,3,9,1,2,3,9,8,9,7,6,9,7,3,9,6,5,6,8,7,8,9,4,2,8,5,8,9,8,9,0,1,2,9,8,7,8,9,9,9,5,3,0,1,2,3,6,7,8,9,4,3,6,8,8,9,7,4,5,4,5,7,9,9,8,4,3,4,9,9,8,6,7,8,9,8,9,6,3,9,8,9,8,7,5,2,1,4,5,6,7,8,9,5,
    2,3,4,5,9,6,5,4,8,5,4,4,6,7,9,7,5,4,3,2,1,2,3,4,5,6,7,8,9,3,7,6,7,8,9,3,2,3,9,8,7,6,7,9,8,5,4,3,2,6,5,4,7,8,9,7,6,4,5,6,9,7,6,3,2,3,4,8,9,9,7,5,4,9,9,8,7,5,6,7,8,9,6,4,2,1,9,9,9,3,2,1,0,8,6,7,8,9,1,4,
    1,4,5,9,8,7,9,8,7,6,5,6,8,9,9,9,8,5,2,1,0,1,2,6,7,8,9,9,5,4,8,7,8,9,6,5,4,9,8,7,6,5,9,8,7,6,5,4,3,4,6,5,9,9,9,8,7,5,6,7,8,9,5,4,3,5,6,9,9,9,8,7,9,8,7,7,6,4,5,6,7,8,9,2,1,0,1,9,8,5,3,2,1,9,9,8,9,1,0,3,
    2,3,4,5,9,8,9,9,8,7,8,7,9,9,9,8,7,6,3,2,5,4,3,4,5,6,7,8,9,5,9,8,9,8,7,6,7,8,9,9,5,3,6,9,8,7,7,5,4,5,7,6,7,8,9,9,8,6,7,8,9,7,6,5,4,5,6,8,9,5,9,9,8,7,6,3,2,3,4,5,9,9,9,3,4,3,2,9,7,6,4,3,2,4,5,9,8,9,1,2,
    3,5,8,9,9,9,6,5,9,8,9,8,9,8,9,9,8,5,4,3,9,5,4,5,6,7,8,9,9,6,7,9,9,9,8,7,8,9,9,8,7,4,5,6,9,9,8,6,5,6,7,9,8,9,6,5,9,7,8,9,7,9,8,7,5,8,7,8,9,4,3,0,9,8,5,4,1,2,3,5,7,8,8,9,6,4,4,9,8,9,5,4,3,4,5,6,7,8,9,3,
    4,6,7,8,9,6,5,4,0,9,5,9,9,7,9,8,7,6,5,9,8,6,5,7,7,8,9,9,8,7,8,9,8,6,9,9,9,8,9,9,6,5,6,7,8,9,9,8,6,7,8,9,9,6,5,4,9,8,9,8,6,9,8,7,6,9,8,9,6,3,2,1,9,7,6,7,0,1,2,4,5,6,7,8,9,5,6,7,9,7,6,5,4,5,9,9,8,9,5,4,
    5,7,8,9,6,5,4,3,1,2,3,4,5,6,7,9,8,7,6,8,9,7,6,8,9,9,1,0,9,8,9,7,5,4,3,4,6,7,9,8,7,8,7,8,9,1,0,9,9,8,9,9,8,7,6,8,9,9,7,6,5,6,9,8,9,9,9,6,5,4,3,9,7,6,5,4,3,2,3,7,6,7,8,9,7,6,8,9,9,8,7,6,5,6,8,9,9,8,6,5,
};

#if 0
#define data data1
#define MAP_WIDTH 10
#define MAP_HEIGHT 5
#else
#define data data2
#define MAP_WIDTH 100
#define MAP_HEIGHT 100
#endif

#define INDEX(x, y) ((y) * MAP_WIDTH + (x))

#define MAX_BASINS 250
#define BASIN_BORDER 9
#define BASIN_POS_VISITED -1

void floodFill(int* map, int x, int y, int* basinSize)
{
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
        return;

    int index = INDEX(x, y);

    if (map[index] != BASIN_BORDER && map[index] != BASIN_POS_VISITED)
    {
        map[index] = BASIN_POS_VISITED;

        (*basinSize)++;

        floodFill(map, x + 1, y, basinSize);
        floodFill(map, x - 1, y, basinSize);
        floodFill(map, x, y + 1, basinSize);
        floodFill(map, x, y - 1, basinSize);
    }
}

bool isLowpoint(int x, int y)
{
    const int offsets[4][2] =
    {
        { 0, -1},
        {-1,  0},
        { 1,  0},
        { 0,  1},
    };

    int value = data[INDEX(x, y)];

    int result = true;
    for (int i = 0; result && i < _countof(offsets); ++i)
    {
        int sx = x + offsets[i][0];
        int sy = y + offsets[i][1];

        if (sx >= 0 && sx < MAP_WIDTH &&
            sy >= 0 && sy < MAP_HEIGHT)
        {
            result &= data[INDEX(sx, sy)] > value;
        }
    }

    return result;
}

int compare(void* a, void* b)
{
    return (*(int*)b - *(int*)a);
}

int main()
{
#if PART == 2
    int basins[MAX_BASINS] = { 0 };
    int numBasins = 0;
#endif

    int result = 0;
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            if (isLowpoint(x, y))
            {
#if PART == 1
                result += data[INDEX(x, y)] + 1;
#else
                int basinSize = 0;
                floodFill(data, x, y, &basinSize);
                assert(numBasins < MAX_BASINS && "too many basins found");
                basins[numBasins++] = basinSize;
#endif
            }
        }
    }

#if PART == 2
    qsort(basins, numBasins, sizeof(int), compare);
    result = 1;
    assert(numBasins >= 3 && "bad input data...");
    for (int i = 0; i < 3; ++i)
    {
        result *= basins[i];
    }
#endif

    printf("%d\n", result);
}