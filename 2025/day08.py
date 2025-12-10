import math
from itertools import combinations

# ------------------------------------------------------------
# Load input from file
# ------------------------------------------------------------
with open("data/day08.txt") as f:
    coords = [tuple(map(int, line.strip().split(",")))
              for line in f if line.strip()]

n = len(coords)
print(f"Loaded {n} junction boxes.")

# ------------------------------------------------------------
# Compute all pairwise distances once
# ------------------------------------------------------------
edges = []
for i, j in combinations(range(n), 2):
    x1, y1, z1 = coords[i]
    x2, y2, z2 = coords[j]
    d = math.sqrt((x1-x2)**2 + (y1-y2)**2 + (z1-z2)**2)
    edges.append((d, i, j))

edges.sort(key=lambda x: x[0])

# ------------------------------------------------------------
# Disjoint Set Union (Union–Find)
# ------------------------------------------------------------
class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
        self.size = [1] * n
        self.groups = n

    def find(self, x):
        while self.parent[x] != x:
            self.parent[x] = self.parent[self.parent[x]]
            x = self.parent[x]
        return x

    def union(self, a, b):
        ra = self.find(a)
        rb = self.find(b)
        if ra == rb:
            return False
        if self.size[ra] < self.size[rb]:
            ra, rb = rb, ra
        self.parent[rb] = ra
        self.size[ra] += self.size[rb]
        self.groups -= 1
        return True

# ------------------------------------------------------------
# PART 1 — After 1000 shortest connections
# ------------------------------------------------------------
K = 1000
dsu1 = DSU(n)

for _, i, j in edges[:K]:
    dsu1.union(i, j)

# Determine circuit sizes
circuit_sizes = {}
for node in range(n):
    root = dsu1.find(node)
    circuit_sizes[root] = circuit_sizes.get(root, 0) + 1

sizes = sorted(circuit_sizes.values(), reverse=True)
part1 = sizes[0] * sizes[1] * sizes[2]

print("Part 1 answer:", part1)

# ------------------------------------------------------------
# PART 2 — Keep connecting until one group remains
# ------------------------------------------------------------
dsu2 = DSU(n)
last_i = last_j = None

for _, i, j in edges:
    if dsu2.union(i, j):
        if dsu2.groups == 1:
            last_i, last_j = i, j
            break

x1 = coords[last_i][0]
x2 = coords[last_j][0]
part2 = x1 * x2

print("Part 2 answer:", part2)
