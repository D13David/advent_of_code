def is_invalid_part1(num):
    s = str(num)
    n = len(s)
    if n % 2 != 0:
        return False
    half = n // 2
    return s[:half] * 2 == s

def is_invalid_part2(num):
    s = str(num)
    n = len(s)
    for l in range(1, n // 2 + 1):
        if n % l == 0 and s == s[:l] * (n // l):
            return True
    return False

def find_invlid_ids(ranges, verify_func):
    total = 0
    for range_str in ranges.split(','):
        start, end = map(int, range_str.split('-'))
        for num in range(start, end + 1):
            if verify_func(num):
                total += num
    return total
    
input_ranges = open("data/day02.txt", "r").read()
print("Part 1:", find_invlid_ids(input_ranges, is_invalid_part1))
print("Part 2:", find_invlid_ids(input_ranges, is_invalid_part2))