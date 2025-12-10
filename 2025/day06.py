import re
import math

def read_grid(lines):
    """
    Parse input lines into a list of operators and a grid of columns.

    The last line contains operators (e.g., '+', '*'), spaced to match the column widths.
    Each preceding line is a row of numbers aligned with the operators.
    """
    ops_line = lines[-1]
    ops = re.findall(r'[^ ]\s*', ops_line)
    ops = [op[:-1] if i < len(ops) - 1 else op for i, op in enumerate(ops)]

    widths = [len(op) for op in ops]
    
    grid = [
        [line[start:start + width] for line in lines[:-1]]
        for start, width in zip(
            [sum(widths[:i]) + i for i in range(len(widths))], widths
        )
    ]

    return [op.strip() for op in ops], grid

def decode_row(col):
    """Convert a column of single-character strings into integers."""
    return [int(n) for n in col]

def decode_column(col):
    """Convert a column of multi-character strings into integers row-wise."""
    return [int("".join(chars)) for chars in zip(*col)]

def calculate(ops, grid, decode_fn):
    """
    Calculate the result for the grid using the specified decoding function.

    Supports '+' (sum) and '*' (product) operators.
    """
    result = 0
    for op, col in zip(ops, grid):
        values = decode_fn(col)
        match op:
            case "+":
                result += sum(values)
            case "*":
                result += math.prod(values)
            case _:
                raise ValueError(f"Unknown operator: {op}")

    return result

if __name__ == "__main__":
    with open("data/day06.txt") as f:
        ops, grid = read_grid(f.readlines())
    
    print(f"Part 1: {calculate(ops, grid, decode_row)}")
    print(f"Part 2: {calculate(ops, grid, decode_column)}")
