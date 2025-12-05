def max_joltage(line, k):
    """Return the largest number formed by choosing k digits in order from the line."""
    stack = []
    n = len(line)
    for i, digit in enumerate(line):
        while stack and stack[-1] < digit and len(stack) + (n - i) > k:
            stack.pop()
        if len(stack) < k:
            stack.append(digit)
    return int(''.join(stack))


with open("data/day03.txt") as f:
    lines = [line.strip() for line in f if line.strip()]

print("Part 1:", sum(max_joltage(line, 2) for line in lines))
print("Part 2:", sum(max_joltage(line, 12) for line in lines))
