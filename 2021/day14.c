#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define PART 2

const char* rules1[] =
{
    "OV",
    "CO",
    "CS",
    "NP",
    "HH",
    "KO",
    "VO",
    "SP",
    "CB",
    "SB",
    "CF",
    "KS",
    "OH",
    "NN",
    "SF",
    "FH",
    "VV",
    "VH",
    "BV",
    "KF",
    "CC",
    "NF",
    "VS",
    "SK",
    "HV",
    "CK",
    "VP",
    "HP",
    "CN",
    "OB",
    "NS",
    "PS",
    "KB",
    "VF",
    "FP",
    "BB",
    "HF",
    "CH",
    "BH",
    "KK",
    "OO",
    "NO",
    "BP",
    "KH",
    "KN",
    "OF",
    "VC",
    "NK",
    "ON",
    "OC",
    "VK",
    "SH",
    "NH",
    "FB",
    "FC",
    "OP",
    "PV",
    "BN",
    "PC",
    "PK",
    "FF",
    "SV",
    "HK",
    "NB",
    "OK",
    "PH",
    "SO",
    "PP",
    "KV",
    "FO",
    "FN",
    "HN",
    "VB",
    "CV",
    "BC",
    "CP",
    "FS",
    "KP",
    "BS",
    "BK",
    "PN",
    "PF",
    "HO",
    "NC",
    "SS",
    "BO",
    "BF",
    "NV",
    "PB",
    "HB",
    "VN",
    "FV",
    "FK",
    "PO",
    "SC",
    "HS",
    "KC",
    "HC",
    "OS",
    "SN",
};
const char target1[] =
{
    'V',
    'V',
    'O',
    'H',
    'P',
    'F',
    'B',
    'O',
    'N',
    'F',
    'S',
    'P',
    'H',
    'O',
    'K',
    'F',
    'B',
    'O',
    'V',
    'K',
    'F',
    'H',
    'O',
    'K',
    'O',
    'K',
    'F',
    'S',
    'K',
    'H',
    'F',
    'S',
    'S',
    'S',
    'H',
    'N',
    'V',
    'N',
    'F',
    'B',
    'N',
    'K',
    'K',
    'P',
    'P',
    'B',
    'F',
    'F',
    'O',
    'P',
    'O',
    'C',
    'C',
    'B',
    'K',
    'O',
    'V',
    'V',
    'K',
    'S',
    'C',
    'S',
    'H',
    'C',
    'C',
    'B',
    'O',
    'F',
    'V',
    'B',
    'H',
    'C',
    'K',
    'O',
    'C',
    'S',
    'S',
    'V',
    'V',
    'B',
    'C',
    'S',
    'V',
    'N',
    'N',
    'P',
    'N',
    'P',
    'K',
    'H',
    'H',
    'B',
    'K',
    'S',
    'S',
    'S',
    'F',
    'S',
    'K',
    'N'
};

const char* polymerTemplate1 = "BCHCKFFHSKPBSNVVKVSK";

const char* rules2[] =
{
    "CH", // -> B
    "HH", // -> N
    "CB", // -> H
    "NH", // -> C
    "HB", // -> C
    "HC", // -> B
    "HN", // -> C
    "NN", // -> C
    "BH", // -> H
    "NC", // -> B
    "NB", // -> B
    "BN", // -> B
    "BB", // -> N
    "BC", // -> B
    "CC", // -> N
    "CN", // -> C
};

const char target2[] =
{
   'B',
   'N',
   'H',
   'C',
   'C',
   'B',
   'C',
   'C',
   'H',
   'B',
   'B',
   'B',
   'N',
   'B',
   'N',
   'C',
};

const char* polymerTemplate2 = "NNCB";

#if 1
#define rules rules1
#define target target1
#define polymerTemplate polymerTemplate1
#else
#define rules rules2
#define target target2
#define polymerTemplate polymerTemplate2
#endif

#define NUM_PAIRS _countof(rules)

__int64* pairsBuffer;
__int64* pairsSource;
__int64* pairsTarget;

int indexOfPair(const char* pair)
{
    for (int i = 0; i < _countof(rules); ++i)
    {
        if (!strcmp(rules[i], pair))
            return i;
    }
    return -1;
}

void initialize()
{
    int size = NUM_PAIRS * 2 * sizeof(__int64);
    pairsBuffer = (__int64*)malloc(size);
    assert(pairsBuffer != NULL && "allocation failed");
    memset(pairsBuffer, 0, size);

    int length = strlen(polymerTemplate);
    for (int i = 1; i < length; ++i)
    {
        char pair[3] = { polymerTemplate[i - 1], polymerTemplate[i] };
        pairsBuffer[indexOfPair(pair)]++;
    }

    pairsSource = pairsBuffer;
    pairsTarget = pairsBuffer + NUM_PAIRS;
}

int main()
{
    initialize();

#if PART == 1
    const int stepsToSimulate = 10;
#else
    const int stepsToSimulate = 40;
#endif

    for (int i = 0; i < stepsToSimulate; ++i)
    {
        memset(pairsTarget, 0, NUM_PAIRS * sizeof(__int64));

        for (int j = 0; j < NUM_PAIRS; ++j)
        {
            __int64 numPairsInCurrentStep = pairsSource[j];
            if (numPairsInCurrentStep > 0)
            {
                char pair1[3] = { rules[j][0], target[j] };
                char pair2[3] = { target[j], rules[j][1] };
                pairsTarget[indexOfPair(pair1)] += numPairsInCurrentStep;
                pairsTarget[indexOfPair(pair2)] += numPairsInCurrentStep;
            }
        }

        __int64* temp = pairsSource;
        pairsSource = pairsTarget;
        pairsTarget = temp;
    }

    __int64 lut[26] = { 0 };
    for (int i = 0; i < NUM_PAIRS; ++i)
    {
        lut[rules[i][0] - 'A'] += pairsSource[i];
        lut[rules[i][1] - 'A'] += pairsSource[i];
    };

    int count = 0;
    for (int i = 0; i < _countof(lut); ++i)
    {
        if (lut[i] > 0)
            lut[count++] = lut[i];
    }

    int max = 0;
    int min = 0;
    for (int i = 1; i < count; ++i)
    {
        if (lut[i] > lut[max])
            max = i;
        if (lut[i] < lut[min])
            min = i;
    }
    printf("%I64d\n", (lut[max] - lut[min]) / 2 + 1);

    free(pairsBuffer);
}