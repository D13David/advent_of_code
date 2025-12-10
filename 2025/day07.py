from collections import deque
from functools import lru_cache

# ------------------------------------------------------------
# PART 1 — Classical tachyon manifold (beam splitting)
# ------------------------------------------------------------
def count_splits(manifold):
    H = len(manifold)
    W = len(manifold[0])

    # locate S
    for r in range(H):
        for c in range(W):
            if manifold[r][c] == 'S':
                start = (r, c)
                break

    beams = deque([start])
    visited = set()
    splits = 0

    while beams:
        r, c = beams.popleft()

        nr = r + 1
        nc = c
        while 0 <= nr < H:
            if (nr, nc) in visited:
                break
            visited.add((nr, nc))

            cell = manifold[nr][nc]

            if cell == '^':
                splits += 1
                # Emit left + right beams
                if nc - 1 >= 0:
                    beams.append((nr, nc - 1))
                if nc + 1 < W:
                    beams.append((nr, nc + 1))
                break

            nr += 1

    return splits


# ------------------------------------------------------------
# PART 2 — Quantum tachyon manifold (many-worlds timelines)
# ------------------------------------------------------------
def count_timelines(manifold):
    H = len(manifold)
    W = len(manifold[0])

    # locate S
    for r in range(H):
        for c in range(W):
            if manifold[r][c] == 'S':
                start = (r, c)
                break

    @lru_cache(None)
    def dfs(r, c):
        """Return number of timelines starting from (r,c)."""
        nr = r + 1
        nc = c

        # Fell out bottom = one timeline ends here
        if nr >= H:
            return 1

        # Move downward until splitter or exit
        while nr < H:
            cell = manifold[nr][nc]

            if cell == '^':
                total = 0
                # left
                if nc - 1 >= 0:
                    total += dfs(nr, nc - 1)
                # right
                if nc + 1 < W:
                    total += dfs(nr, nc + 1)
                return total

            nr += 1

        # Reached bottom with no more splitters
        return 1

    return dfs(start[0], start[1])


# ------------------------------------------------------------
# MAIN PROGRAM
# ------------------------------------------------------------
if __name__ == "__main__":
    with open("data/day07.txt") as f:
        manifold = [line.rstrip("\n") for line in f]

    p1 = count_splits(manifold)
    p2 = count_timelines(manifold)

    print("Part 1:", p1)
    print("Part 2:", p2)
