from __future__ import annotations
from itertools import combinations
import bisect
from pathlib import Path


def part2(points):
    # Build horizontal and vertical edges
    horizontal_edges = []
    vertical_edges = []

    n = len(points)
    for i in range(n):
        x1, y1 = points[i]
        x2, y2 = points[(i + 1) % n]

        if x1 == x2:
            vertical_edges.append((min(y1, y2), max(y1, y2), x1))
        else:
            horizontal_edges.append((min(x1, x2), max(x1, x2), y1))

    # Longest edges
    longest_h = max(horizontal_edges, key=lambda t: t[1] - t[0])
    longest_v = max(vertical_edges, key=lambda t: t[1] - t[0])

    # Sort for bisect
    horizontal_edges.sort(key=lambda h: h[2])
    vertical_edges.sort(key=lambda v: v[2])

    h_y_coords = [h[2] for h in horizontal_edges]
    v_x_coords = [v[2] for v in vertical_edges]

    largest_area = 0
    best_rect = None

    # Function to check rectangle validity
    def is_valid(x1, y1, x2, y2):
        rect = (x1, y1, x2, y2)
        rx1, ry1, rx2, ry2 = rect

        # Longest horizontal
        hx1, hx2, hy = longest_h
        if ry1 < hy < ry2 and (hx1 < rx2 <= hx2 or hx1 <= rx1 < hx2):
            return False

        # Longest vertical
        vy1, vy2, vx = longest_v
        if rx1 < vx < rx2 and (vy1 < ry2 <= vy2 or vy1 <= ry1 < vy2):
            return False

        # Check horizontal edges
        h_start = bisect.bisect_right(h_y_coords, ry1)
        h_end = bisect.bisect_left(h_y_coords, ry2)
        if any(ex1 < rx2 <= ex2 or ex1 <= rx1 < ex2
               for ex1, ex2, ey in horizontal_edges[h_start:h_end]):
            return False

        # Check vertical edges
        v_start = bisect.bisect_right(v_x_coords, rx1)
        v_end = bisect.bisect_left(v_x_coords, rx2)
        if any(ey1 < ry2 <= ey2 or ey1 <= ry1 < ey2
               for ey1, ey2, ex in vertical_edges[v_start:v_end]):
            return False

        return True

    # Iterate all pairs
    for (x1, y1), (x2, y2) in combinations(points, 2):
        rx1, ry1, rx2, ry2 = min(x1, x2), min(y1, y2), max(x1, x2), max(y1, y2)
        area = (rx2 - rx1 + 1) * (ry2 - ry1 + 1)

        if area <= largest_area:
            continue

        if is_valid(rx1, ry1, rx2, ry2):
            largest_area = area
            best_rect = ((x1, y1), (x2, y2))

    return largest_area, best_rect


# ─────────────────────────────────────────────────────────────────────────────
# Part 1
# ─────────────────────────────────────────────────────────────────────────────

def part1(points):
    largest = 0
    for (ax, ay), (bx, by) in combinations(points, 2):
        area = (abs(ax - bx) + 1) * (abs(ay - by) + 1)
        largest = max(largest, area)
    return largest


def load_data(filename):
    return [tuple(map(int, line.split(',')))
            for line in Path(filename).read_text().splitlines()]


if __name__ == "__main__":
    data = load_data("data/day09.txt")

    ans1 = part1(data)
    print("Part 1:", ans1)

    ans2 = part2(data)
    print("Part 2:", ans2)
