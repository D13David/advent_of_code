from itertools import product

# ------------------------
# Shape helpers
# ------------------------
def rotate(shape):
    return ["".join(row) for row in zip(*shape[::-1])]

def flip(shape):
    return [row[::-1] for row in shape]

def shape_to_coords(shape):
    return [(x, y) for y, row in enumerate(shape) for x, c in enumerate(row) if c == "#"]

def generate_variants(shape):
    variants = set()
    s = shape
    for _ in range(4):
        s = rotate(s)
        for f in [s, flip(s)]:
            coords = tuple(sorted(shape_to_coords(f)))
            variants.add(coords)
    return list(variants)

# ------------------------
# Backtracking solver
# ------------------------
def can_place(grid, w, h, piece, ox, oy):
    for x, y in piece:
        nx, ny = ox + x, oy + y
        if nx < 0 or ny < 0 or nx >= w or ny >= h:
            return False
        if grid[ny][nx] != 0:
            return False
    return True

def place(grid, piece, ox, oy, val):
    for x, y in piece:
        grid[oy + y][ox + x] = val

def solve(grid, w, h, shapes, counts, shape_ids):
    if not shapes:
        return True
    idx = 0
    while idx < len(shapes) and counts[idx] == 0:
        idx += 1
    if idx == len(shapes):
        return True
    for variant in shape_ids[idx]:
        max_x = w - max(x for x, y in variant)
        max_y = h - max(y for x, y in variant)
        for ox in range(max_x):
            for oy in range(max_y):
                if can_place(grid, w, h, variant, ox, oy):
                    counts[idx] -= 1
                    place(grid, variant, ox, oy, idx + 1)
                    if solve(grid, w, h, shapes, counts, shape_ids):
                        return True
                    place(grid, variant, ox, oy, 0)
                    counts[idx] += 1
    return False

shapes_input = []
regions_input = []

with open("data/day12.txt") as f:
    lines = [line.rstrip() for line in f if line.strip()]

# Parse shapes
i = 0
while i < len(lines):
    if lines[i].endswith(":"):
        shape = []
        i += 1
        # read shape rows until next index or region line
        while i < len(lines) and not lines[i].endswith(":") and "x" not in lines[i]:
            shape.append(lines[i])
            i += 1
        shapes_input.append(shape)
    else:
        i += 1

# Parse regions
for line in lines:
    if "x" in line and ":" in line:
        size_part, counts_part = line.split(":")
        w, h = map(int, size_part.split("x"))
        counts = list(map(int, counts_part.split()))
        regions_input.append((w, h, counts))

# Precompute variants
shape_ids = [generate_variants(s) for s in shapes_input]

# ------------------------
# Solve
# ------------------------
valid_count = 0
for w, h, counts in regions_input:
    total_area_needed = sum(len(next(iter(shape_ids[i]))) * c for i, c in enumerate(counts))
    if total_area_needed > w * h:
        continue
    grid = [[0]*w for _ in range(h)]
    counts_copy = counts[:]
    if solve(grid, w, h, shapes_input, counts_copy, shape_ids):
        valid_count += 1

print("Regions that can fit all presents:", valid_count)
