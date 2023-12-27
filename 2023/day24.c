#include "day24.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>

#define PART 2

#define NUM_HAILSTONES (sizeof(data) / sizeof(data[0]))

#define TEST_AREA_MIN   200000000000000.0
#define TEST_AREA_MAX   400000000000000.0

typedef struct hailstone_s
{
    double px, py, pz;
    int vx, vy, vz;
    double slope;
    double intercept;
} hailstone_t;

hailstone_t hailstones[NUM_HAILSTONES];

void cross(double a1, double a2, double a3, double b1, double b2, double b3, double* s1, double* s2, double* s3)
{
    *s1 = a2 * b3 - a3 * b2;
    *s2 = a3 * b1 - a1 * b3;
    *s3 = a1 * b2 - a2 * b1;
}

int invertMatrix(double matrix[6][6], double result[6][6]) 
{
    for (int i = 0; i < 6; i++) 
    {
        for (int j = 0; j < 6; j++) {
            result[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    for (int i = 0; i < 6; i++) 
    {
        int pivotRow = i;
        while (matrix[pivotRow][i] == 0) 
        {
            pivotRow++;
            if (pivotRow == 6) {
                return 0;
            }
        }

        if (pivotRow != i) 
        {
            for (int j = 0; j < 6; j++) 
            {
                double temp = matrix[i][j];
                matrix[i][j] = matrix[pivotRow][j];
                matrix[pivotRow][j] = temp;

                temp = result[i][j];
                result[i][j] = result[pivotRow][j];
                result[pivotRow][j] = temp;
            }
        }

        double scale = 1.0 / matrix[i][i];
        for (int j = 0; j < 6; j++) 
        {
            matrix[i][j] *= scale;
            result[i][j] *= scale;
        }

        for (int j = 0; j < 6; j++) 
        {
            if (j == i) {
                continue;
            }

            const double factor = -matrix[j][i];
            for (int k = 0; k < 6; k++) 
            {
                matrix[j][k] += factor * matrix[i][k];
                result[j][k] += factor * result[i][k];
            }
        }
    }
}

main()
{
    for (int i = 0; i < NUM_HAILSTONES; ++i)
    {
        unsigned __int64 px, py, pz;
        int result = sscanf(data[i], "%lld, %lld, %lld @ %d, %d, %d", &px, &py, &pz,
            &hailstones[i].vx, &hailstones[i].vy, &hailstones[i].vz);
        assert(result == 6);

        hailstones[i].px = (double)px;
        hailstones[i].py = (double)py;
        hailstones[i].pz = (double)pz;
        hailstones[i].slope = (double)hailstones[i].vy / hailstones[i].vx;
        hailstones[i].intercept = hailstones[i].py - (hailstones[i].slope * hailstones[i].px);
    }

    unsigned __int64 sum = 0;

#if PART == 1
    for (int i = 0; i < NUM_HAILSTONES; ++i)
    {
        for (int j = i + 1; j < NUM_HAILSTONES; ++j)
        {
            if (fabs(hailstones[i].slope - hailstones[j].slope) < 0.000001 &&
                fabs(hailstones[i].intercept - hailstones[j].intercept) < 0.000001)
            {
                sum++;
            }

            const double tmp1 = (hailstones[i].intercept - hailstones[j].intercept) / (hailstones[j].slope - hailstones[i].slope);
            const double tmp2 = (hailstones[i].slope * tmp1) + hailstones[i].intercept;

            if (tmp1 >= TEST_AREA_MIN && tmp1 <= TEST_AREA_MAX && tmp2 >= TEST_AREA_MIN && tmp2 <= TEST_AREA_MAX)
            {
                int checkCoord1 = ((tmp1 > hailstones[i].px && hailstones[i].vx > 0) ||
                    (tmp1 < hailstones[i].px && hailstones[i].vx < 0) ||
                    (tmp2 > hailstones[i].py && hailstones[i].vy > 0) ||
                    (tmp2 < hailstones[i].py && hailstones[i].vy < 0));

                int checkCoord2 = ((tmp1 > hailstones[j].px && hailstones[j].vx > 0) ||
                    (tmp1 < hailstones[j].px && hailstones[j].vx < 0) ||
                    (tmp2 > hailstones[j].py && hailstones[j].vy > 0) ||
                    (tmp2 < hailstones[j].py && hailstones[j].vy < 0));

                if (checkCoord1 && checkCoord2) {
                    ++sum;
                }
            }
        }
    }
#else
    // took this idea from reddit aoc 2023 day 24 thread :)
    double m[6][6];
    double v[6];

    double tmp[3];
    cross(hailstones[0].px, hailstones[0].py, hailstones[0].pz,
        hailstones[0].vx, hailstones[0].vy, hailstones[0].vz,
        &tmp[0], &tmp[1], &tmp[2]);

    v[0] = -tmp[0];
    v[1] = -tmp[1];
    v[2] = -tmp[2];

    cross(hailstones[1].px, hailstones[1].py, hailstones[1].pz,
        hailstones[1].vx, hailstones[1].vy, hailstones[1].vz,
        &tmp[0], &tmp[1], &tmp[2]);

    v[0] += tmp[0];
    v[1] += tmp[1];
    v[2] += tmp[2];

    cross(hailstones[0].px, hailstones[0].py, hailstones[0].pz,
        hailstones[0].vx, hailstones[0].vy, hailstones[0].vz,
        &tmp[0], &tmp[1], &tmp[2]);

    v[3] = -tmp[0];
    v[4] = -tmp[1];
    v[5] = -tmp[2];

    cross(hailstones[2].px, hailstones[2].py, hailstones[2].pz,
        hailstones[2].vx, hailstones[2].vy, hailstones[2].vz,
        &tmp[0], &tmp[1], &tmp[2]);

    v[3] += tmp[0];
    v[4] += tmp[1];
    v[5] += tmp[2];

    // top left
    m[0][0] = 0; 
    m[0][1] = hailstones[0].vz - hailstones[1].vz;
    m[0][2] = -hailstones[0].vy + hailstones[1].vy;

    m[1][0] = -hailstones[0].vz + hailstones[1].vz;
    m[1][1] = 0;
    m[1][2] = hailstones[0].vx - hailstones[1].vx;

    m[2][0] = hailstones[0].vy - hailstones[1].vy;
    m[2][1] = -hailstones[0].vx + hailstones[1].vx;
    m[2][2] = 0;

    // top right
    m[0][3] = 0;
    m[0][4] = hailstones[0].vz - hailstones[2].vz;
    m[0][5] = -hailstones[0].vy + hailstones[2].vy;

    m[1][3] = -hailstones[0].vz + hailstones[2].vz;
    m[1][4] = 0;
    m[1][5] = hailstones[0].vx - hailstones[2].vx;

    m[2][3] = hailstones[0].vy - hailstones[2].vy;
    m[2][4] = -hailstones[0].vx + hailstones[2].vx;
    m[2][5] = 0;

    // bottom left
    m[3][0] = 0;
    m[3][1] = -hailstones[0].pz + hailstones[1].pz;
    m[3][2] = hailstones[0].py - hailstones[1].py;

    m[4][0] = hailstones[0].pz - hailstones[1].pz;
    m[4][1] = 0;
    m[4][2] = -hailstones[0].px + hailstones[1].px;

    m[5][0] = -hailstones[0].py + hailstones[1].py;
    m[5][1] = hailstones[0].px - hailstones[1].px;
    m[5][2] = 0;

    // bottom right
    m[3][3] = 0;
    m[3][4] = -hailstones[0].pz + hailstones[2].pz;
    m[3][5] = hailstones[0].py - hailstones[2].py;

    m[4][3] = hailstones[0].pz - hailstones[2].pz;
    m[4][4] = 0;
    m[4][5] = -hailstones[0].px + hailstones[2].px;

    m[5][3] = -hailstones[0].py + hailstones[2].py;
    m[5][4] = hailstones[0].px - hailstones[2].px;
    m[5][5] = 0;

    double m1[6][6];
    invertMatrix(m, m1);

    double result[6];

    for (int y = 0; y < 5; ++y)
    {
        result[y] = m1[0][y] * v[0] + 
                    m1[1][y] * v[1] +
                    m1[2][y] * v[2] +
                    m1[3][y] * v[3] +
                    m1[4][y] * v[4] +
                    m1[5][y] * v[5];
    }

    sum = (unsigned __int64)(result[0] - 0.5) + 
        (unsigned __int64)(result[1] - 0.5) +
        (unsigned __int64)(result[2] - 0.5);
#endif

    printf("%lld\n", sum);
}
