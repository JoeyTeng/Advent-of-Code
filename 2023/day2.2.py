import math
import re
import sys

patterns = (
    re.compile(r"([\d]+) red"),
    re.compile(r"([\d]+) green"),
    re.compile(r"([\d]+) blue"),
)

sum_powers = 0

for index, line in enumerate(sys.stdin.readlines(), start=1):
    records = line.split(":")[1]
    game_sets = records.split(";")
    min_rgb = [0, 0, 0]
    for game_set in game_sets:
        for i, pattern in enumerate(patterns):
            number = pattern.search(game_set)
            if number:
                min_rgb[i] = max(min_rgb[i], int(number.group(1)))

    sum_powers += math.prod(min_rgb)

print(sum_powers)
