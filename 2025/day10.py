from functools import lru_cache
import pulp

# ------------------------------------------------------------
# Parsing
# ------------------------------------------------------------
def parse_line(line):
    line = line.strip()
    # indicator pattern
    ind_start = line.index('[')
    ind_end = line.index(']')
    indicator = line[ind_start+1 : ind_end]

    # buttons
    buttons = []
    i = ind_end + 1
    while True:
        try:
            p1 = line.index('(', i)
            p2 = line.index(')', p1)
        except ValueError:
            break
        inside = line[p1+1:p2].strip()
        if inside:
            btn = list(map(int, inside.split(',')))
        else:
            btn = []
        buttons.append(btn)
        i = p2 + 1

    # jolts
    jolts_start = line.index('{')
    jolts_end = line.index('}')
    jolts = list(map(int, line[jolts_start+1:jolts_end].split(',')))

    return indicator, buttons, jolts

# ------------------------------------------------------------
# Part 1: GF(2) solver (toggle system)
# ------------------------------------------------------------
def solve_machine_gf2(pattern, buttons):
    n = len(pattern)
    m = len(buttons)
    target = [1 if c == '#' else 0 for c in pattern]

    # Build matrix A (n x m)
    A = [[0]*m for _ in range(n)]
    for j, btn in enumerate(buttons):
        for idx in btn:
            A[idx][j] ^= 1

    # Gaussian elimination over GF(2)
    A = [row[:] for row in A]
    b = target[:]

    row = 0
    pivot_cols = []

    for col in range(m):
        pivot = None
        for r in range(row, n):
            if A[r][col] == 1:
                pivot = r
                break
        if pivot is None:
            continue

        # Swap
        A[row], A[pivot] = A[pivot], A[row]
        b[row], b[pivot] = b[pivot], b[row]

        pivot_cols.append(col)

        # Eliminate
        for r in range(n):
            if r != row and A[r][col] == 1:
                for c in range(col, m):
                    A[r][c] ^= A[row][c]
                b[r] ^= b[row]

        row += 1
        if row == n:
            break

    # Check consistency
    for r in range(row, n):
        if b[r] == 1 and all(v == 0 for v in A[r]):
            return None  # no solution

    # Determine pivot and free variables
    pivots = pivot_cols
    free_cols = [c for c in range(m) if c not in pivots]

    # Build particular solution (all free vars = 0)
    x0 = [0]*m
    r = 0
    for pc in pivots:
        x0[pc] = b[r]
        r += 1

    # Build basis vectors for free variables
    basis = []
    for f in free_cols:
        v = [0]*m
        v[f] = 1
        r = 0
        for pc in pivots:
            s = 0
            for ff in free_cols:
                if A[r][ff] == 1 and ff == f:
                    s ^= 1
            v[pc] = s
            r += 1
        basis.append(v)

    # Try all 2^(#free) solutions, choose minimum Hamming weight
    best = float('inf')
    k = len(basis)
    for mask in range(1 << k):
        cand = x0[:]
        for i in range(k):
            if (mask >> i) & 1:
                for c in range(m):
                    cand[c] ^= basis[i][c]
        w = sum(cand)
        best = min(best, w)

    return best

# ------------------------------------------------------------
# Part 2: Fast ILP solver using pulp
# ------------------------------------------------------------
def solve_joltage_ilp(buttons, target):
    m = len(buttons)
    k = len(target)

    # Build A matrix
    A = [[0]*m for _ in range(k)]
    for j, btn in enumerate(buttons):
        for idx in btn:
            A[idx][j] = 1

    # Define ILP problem
    prob = pulp.LpProblem("MinButtonPresses", pulp.LpMinimize)
    x_vars = [pulp.LpVariable(f"x{j}", lowBound=0, cat='Integer') for j in range(m)]

    # Objective
    prob += pulp.lpSum(x_vars)

    # Constraints
    for i in range(k):
        prob += pulp.lpSum(A[i][j]*x_vars[j] for j in range(m)) == target[i]

    # Solve
    prob.solve(pulp.PULP_CBC_CMD(msg=0))

    return int(sum(var.varValue for var in x_vars))

# ------------------------------------------------------------
# Main: compute both parts
# ------------------------------------------------------------
def main():
    part1 = 0
    part2 = 0

    with open("data/day10.txt") as f:
        for line in f:
            if not line.strip():
                continue
            indicator, buttons, jolts = parse_line(line)

            # Part 1
            presses1 = solve_machine_gf2(indicator, buttons)
            part1 += presses1

            # Part 2
            presses2 = solve_joltage_ilp(buttons, jolts)
            part2 += presses2

    print("Part 1 minimum total presses:", part1)
    print("Part 2 minimum total joltage presses:", part2)

if __name__ == "__main__":
    main()
