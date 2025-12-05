# Read the grid
with open("data/day04.txt") as f:
    grid = [list(line.strip()) for line in f if line.strip()]

rows = len(grid)
cols = len(grid[0])
directions = [(-1, -1), (-1, 0), (-1, 1),
              (0, -1),          (0, 1),
              (1, -1),  (1, 0), (1, 1)]

# Part 1: count initially accessible rolls
def count_accessible(current_grid):
    accessible_count = 0
    for r in range(rows):
        for c in range(cols):
            if current_grid[r][c] == '@':
                neighbor_count = 0
                for dr, dc in directions:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < rows and 0 <= nc < cols:
                        if current_grid[nr][nc] == '@':
                            neighbor_count += 1
                if neighbor_count < 4:
                    accessible_count += 1
    return accessible_count

part1_result = count_accessible(grid)
print("Part 1:", part1_result)

# Part 2: simulate iterative removal
import copy
grid_copy = copy.deepcopy(grid)
total_removed = 0

while True:
    to_remove = []
    for r in range(rows):
        for c in range(cols):
            if grid_copy[r][c] == '@':
                neighbor_count = 0
                for dr, dc in directions:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < rows and 0 <= nc < cols:
                        if grid_copy[nr][nc] == '@':
                            neighbor_count += 1
                if neighbor_count < 4:
                    to_remove.append((r, c))

    if not to_remove:
        break

    for r, c in to_remove:
        grid_copy[r][c] = '.'

    total_removed += len(to_remove)

print("Part 2:", total_removed)
