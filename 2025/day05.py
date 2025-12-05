def parse_input(path):
    with open(path, "r") as f:
        lines = [line.strip() for line in f.readlines()]

    blank_index = lines.index("")

    range_lines = lines[:blank_index]
    ranges = []
    for r in range_lines:
        lo, hi = map(int, r.split("-"))
        ranges.append((lo, hi))

    id_lines = lines[blank_index + 1:]
    ids = [int(x) for x in id_lines]

    return ranges, ids


def solve_part1(ranges, ids):
    return sum(any(lo <= x <= hi for lo, hi in ranges) for x in ids)


def solve_part2(ranges):
    ranges = sorted(ranges)

    merged = []
    cur_lo, cur_hi = ranges[0]

    for lo, hi in ranges[1:]:
        if lo <= cur_hi + 1:
            cur_hi = max(cur_hi, hi)
        else:
            merged.append((cur_lo, cur_hi))
            cur_lo, cur_hi = lo, hi

    merged.append((cur_lo, cur_hi))

    return sum(hi - lo + 1 for lo, hi in merged)


def main():
    ranges, ids = parse_input("data/day05.txt")

    part1 = solve_part1(ranges, ids)
    part2 = solve_part2(ranges)

    print("Part 1:", part1)
    print("Part 2:", part2)


if __name__ == "__main__":
    main()
