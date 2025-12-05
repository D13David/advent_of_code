DIAL_MAX = 100

def part1(data, dial=50):
    password = 0

    for direction, amount in data:
        if direction == "L":
            dial = (dial + DIAL_MAX - amount) % DIAL_MAX
        else:
            dial = (dial + amount) % DIAL_MAX

        if dial == 0: password += 1

    return password

def part2(data, dial=50):
    password = 0

    for direction, amount in data:
        zeros_passed = amount // DIAL_MAX
        amount -= zeros_passed * DIAL_MAX

        if direction == "L":
            zeros_passed += dial > 0 and amount >= dial
            dial = (dial - amount) % DIAL_MAX
        else:
            zeros_passed += amount >= (DIAL_MAX - dial)
            dial = (dial + amount) % DIAL_MAX

        password += zeros_passed

    return password

with open("data/day01.txt", "r") as file:
    data = [(item[0], int(item[1:])) for item in file.read().splitlines()]

print(f"Part 1: {part1(data)}")
print(f"Part 2: {part2(data)}")