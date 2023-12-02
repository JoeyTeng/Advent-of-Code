import re
import sys

patterns = (
    re.compile(r"([\d]+) red"),
    re.compile(r"([\d]+) green"),
    re.compile(r"([\d]+) blue"),
)
limits = (12, 13, 14)

sum_ids = 0

for index, line in enumerate(sys.stdin.readlines(), start=1):
    records = line.split(":")[1]
    game_sets = records.split(";")
    for game_set in game_sets:
        for pattern, limit in zip(patterns, limits):
            number = pattern.search(game_set)
            if number and int(number.group(1)) > limit:
                break
        else:
            continue
        break
    else:
        sum_ids += index

print(sum_ids)
