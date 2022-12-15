#include <stdio.h>
#include <math.h>

#include "DAY15.H"

#define DAY 2

#define NUM_SENSORS (sizeof(data)/sizeof(data[0]))

#define ROW_Y_COORD 2000000
#define MAX_SPACE_DIM 4000000

typedef struct sensor
{
	int posx, posy;
	int bx, by;
	int radius;
} sensor_t;

sensor_t sensors[NUM_SENSORS];

void parseInput(sensor_t* sensors);
void part1(void);
void part2(void);

main()
{
	parseInput(sensors);

#if DAY == 1
	part1();
#else
	part2();
#endif

	return 0;
}

void parseInput(sensor_t* sensors)
{
	int i;

	for (i = 0; i < NUM_SENSORS; ++i)
	{
		sscanf(data[i], "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d",
			&sensors[i].posx, &sensors[i].posy,
			&sensors[i].bx, &sensors[i].by);

		sensors[i].radius = abs(sensors[i].posx - sensors[i].bx) 
			+ abs(sensors[i].posy - sensors[i].by);
	}
}

int min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}
int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

void part1(void)
{
	int i, j, dist, sum;
	int overlapping = 0, numBeacons = 0;
	int ranges[NUM_SENSORS][2], beacons[NUM_SENSORS], minX = 999999999, maxX = -999999999;

	for (i = 0; i < NUM_SENSORS; ++i)
	{
		dist = sensors[i].radius - abs(ROW_Y_COORD - sensors[i].posy);
		if (dist >= 0)
		{
			ranges[overlapping][0] = sensors[i].posx - dist;
			ranges[overlapping][1] = sensors[i].posx + dist;
			minX = min(minX, ranges[overlapping][0]);
			maxX = max(maxX, ranges[overlapping][1]);
			++overlapping;
		}

		if (sensors[i].by == ROW_Y_COORD) {
			beacons[numBeacons++] = sensors[i].bx;
		}
	}

	for (i = minX, sum = 0; i <= maxX; ++i)
	{
		for (j = 0; j < numBeacons; ++j)
		{
			if (beacons[j] == i)
			{
				break;
			}
		}

		if (j < numBeacons) {
			continue;
		}

		for (j = 0; j < overlapping; ++j)
		{
			if (i >= ranges[j][0] && i <= ranges[j][1])
			{
				++sum;
				break;
			}
		}
	}
	printf("%d positions cannot contain a beacon\n", sum);
}

void part2(void)
{
	int i, j, k;
	int px, py, dist;
	int yintercept[2][NUM_SENSORS * 2];

	for (i = 0; i < NUM_SENSORS; ++i)
	{
		yintercept[0][i * 2 + 0] = sensors[i].posy - sensors[i].posx + sensors[i].radius + 1;
		yintercept[0][i * 2 + 1] = sensors[i].posy - sensors[i].posx - sensors[i].radius - 1;
		yintercept[1][i * 2 + 0] = sensors[i].posx + sensors[i].posy + sensors[i].radius + 1;
		yintercept[1][i * 2 + 1] = sensors[i].posx + sensors[i].posy - sensors[i].radius - 1;
	}

	for (i = 0; i < NUM_SENSORS * 2; ++i)
	{
		for (j = 0; j < NUM_SENSORS * 2; ++j)
		{
			px = (yintercept[1][j] - yintercept[0][i]) / 2;
			py = (yintercept[1][j] + yintercept[0][i]) / 2;

			if (px < 0 || px > MAX_SPACE_DIM || py < 0 || py > MAX_SPACE_DIM) {
				continue;
			}

			for (k = 0; k < NUM_SENSORS; ++k)
			{
				dist = abs(px - sensors[k].posx) + abs(py - sensors[k].posy);
				if (dist <= sensors[k].radius) {
					break;
				}
			}

			if (k >= NUM_SENSORS) {
				goto done;
			}
		}
	}
done:
	printf("The tuning frequency is %lld", (long long)px * 4000000 + py);
}