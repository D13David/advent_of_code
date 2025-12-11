from collections import defaultdict

def load_graph(filename):
    graph = defaultdict(list)
    with open(filename) as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            name, outs = line.split(":")
            name = name.strip()
            for tgt in outs.split():
                graph[name].append(tgt)
    return graph


# ------------------ PART 1 ------------------ #
def count_paths_part1(graph, start="you", end="out"):
    memo = {}

    def dfs(node):
        if node == end:
            return 1
        if node in memo:
            return memo[node]
        total = 0
        for nxt in graph[node]:
            total += dfs(nxt)
        memo[node] = total
        return total

    return dfs(start)


# ------------------ PART 2 (FAST) ------------------ #
# bitmask: 0 = visited none, 1 = dac, 2 = fft, 3 = both
def count_paths_part2(graph, start="svr", end="out", dac="dac", fft="fft"):
    memo = {}

    def dfs(node, mask):
        # update visitation mask
        if node == dac:
            mask |= 1
        elif node == fft:
            mask |= 2

        if node == end:
            return 1 if mask == 3 else 0

        key = (node, mask)
        if key in memo:
            return memo[key]

        total = 0
        for nxt in graph[node]:
            total += dfs(nxt, mask)

        memo[key] = total
        return total

    return dfs(start, 0)


# ------------------ MAIN EXECUTION ------------------ #
if __name__ == "__main__":
    graph = load_graph("data/day11.txt")

    # Part 1
    part1_ans = count_paths_part1(graph)
    print("Part 1: ", part1_ans)

    # Part 2 (fast)
    part2_ans = count_paths_part2(graph)
    print("Part 2: ", part2_ans)
