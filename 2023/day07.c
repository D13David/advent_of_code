#include "day07.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define PART                   2

#define NUM_HANDS (sizeof(data) / sizeof(data[0]))

#define HAND_SIZE              5
#define HAND_TYPE_COUNT        7

#define HAND_TYPE_HIGH_CARD    0
#define HAND_TYPE_ONE_PAIR     1
#define HAND_TYPE_TWO_PAIR     2
#define HAND_TYPE_THREE        3
#define HAND_TYPE_FULLHOUSE    4
#define HAND_TYPE_FOUR         5
#define HAND_TYPE_FIVE         6
#define HAND_TYPE_UNKNOWN     -1

int getCardValue(char card)
{
    switch (card)
    {
    case 'A': return 12;
    case 'K': return 11;
    case 'Q': return 10;
#if PART == 1
    case 'J': return 9;
#endif
    case 'T': return 8;
    case '9': return 7;
    case '8': return 6;
    case '7': return 5;
    case '6': return 4;
    case '5': return 3;
    case '4': return 2;
    case '3': return 1;
    case '2': return 0;
    }
    return -1;
}

int cmpStr(const void* a, const void* b)
{
    return strcmp((const char*)a, (const char*)b);
}

int cmpInt(const void* a, const void* b)
{
    return (*(const int*)b) - (*(const int*)a);
}

int cmpHands(const void* a, const void* b)
{
    int index0 = *(const int**)a;
    int index1 = *(const int**)b;

    for (int i = 0; i < HAND_SIZE; ++i)
    {
        int leftValue = getCardValue(data[index0][i]);
        int rightValue = getCardValue(data[index1][i]);
        if (leftValue < rightValue) {
            return 1;
        }
        if (rightValue < leftValue) {
            return -1;
        }
    }

    return 0;
}

int classifyHand(const char* hand)
{
    int numCounts;
    int counts[HAND_SIZE];
    char buffer[HAND_SIZE + 1];
    
    strcpy(buffer, hand);

    qsort(buffer, HAND_SIZE, sizeof(buffer[0]), cmpStr);

    numCounts = 0;
    for (int i = 1, count = 1; i <= HAND_SIZE; ++i)
    {
        if (buffer[i] == buffer[i - 1]) {
            ++count;
        }
        else
        {
            counts[numCounts++] = count;
            count = 1;
        }
    }

    qsort(counts, numCounts, sizeof(counts[0]), cmpInt);

    if (counts[0] == 5) {
        return HAND_TYPE_FIVE;
    }

    if (counts[0] == 4)
    {
        return HAND_TYPE_FOUR;
    }

    if (counts[0] == 3)
    {
        return numCounts == 2 ? HAND_TYPE_FULLHOUSE : HAND_TYPE_THREE;
    }

    if (counts[0] == 2) {
        return counts[1] == 2 ? HAND_TYPE_TWO_PAIR : HAND_TYPE_ONE_PAIR;
    }

    if (numCounts == 5) {
        return HAND_TYPE_HIGH_CARD;
    }

    return HAND_TYPE_UNKNOWN;
}

#if PART == 2
void swap(char* str, int i, int j)
{
    char temp = str[i];
    str[i] = str[j];
    str[j] = temp;
}

int classifyHand_r(char* str, int index) {
    if (index == HAND_SIZE) {
        return classifyHand(str);
    }

    int result = HAND_TYPE_UNKNOWN;

    if (str[index] == 'J') 
    {
        const char alphabet[] = { 'A','K','Q','T','9','8','7','6','5','4','3','2' };
        for (int i = 0; i < sizeof(alphabet)/sizeof(alphabet[0]); ++i)
        {
            str[index] = alphabet[i];
            int type = classifyHand_r(str, index + 1);
            if (type > result) {
                result = type;
            }
        }

        str[index] = 'J';
    }
    else 
    {
        int type = classifyHand_r(str, index + 1);
        if (type > result) {
            result = type;
        }
    }
    return result;
}
#endif

main()
{
    char hand[HAND_SIZE+1];
    int bids[NUM_HANDS];

    int handTypeBuckets[HAND_TYPE_COUNT][NUM_HANDS];
    int numHandsInBuckts[HAND_TYPE_COUNT];

    memset(&numHandsInBuckts, 0, sizeof(numHandsInBuckts));

    for (int i = 0; i < NUM_HANDS; ++i)
    {
        int result = sscanf(data[i], "%5[AKQJT2-9] %d", hand, &bids[i]);
        assert(result == 2);
#if PART == 1
        int handType = classifyHand(hand);
#else
        int handType = classifyHand_r(hand, 0);
#endif
        handTypeBuckets[handType][numHandsInBuckts[handType]++] = i;
    }

    int rank = NUM_HANDS;
    unsigned __int64 total = 0;
    for (int i = HAND_TYPE_COUNT-1; i >= 0; --i)
    {
        qsort(&handTypeBuckets[i], numHandsInBuckts[i], sizeof(handTypeBuckets[i][0]), cmpHands);

        for (int j = 0; j < numHandsInBuckts[i]; ++j, --rank)
        {
            total += bids[handTypeBuckets[i][j]] * rank;
        }
    }

    printf("%lld\n", total);
}