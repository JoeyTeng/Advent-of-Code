# https://adventofcode.com/2023/day/4
import re
import sys

numbers_pattern = re.compile(r"[\d]+")
matches: list[int] = []

for index, line in enumerate(sys.stdin.readlines(), start=1):
    records = line.split(":")[1]
    winning_card, my_card = records.split("|")
    winning_nums = set(map(int, numbers_pattern.findall(winning_card)))
    my_nums = set(map(int, numbers_pattern.findall(my_card)))

    count = len(winning_nums.intersection(my_nums))
    matches.append(count)

instances: list[int] = [1 for _ in matches]

for i, (count, match) in enumerate(zip(instances, matches)):
    for j in range(i + 1, i + 1 + match):
        instances[j] += count

print(sum(instances))
