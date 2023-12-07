# https://adventofcode.com/2023/day/4
import re
import sys

sum_points = 0
numbers_pattern = re.compile(r"[\d]+")

for index, line in enumerate(sys.stdin.readlines(), start=1):
    records = line.split(":")[1]
    winning_card, my_card = records.split("|")
    winning_nums = set(map(int, numbers_pattern.findall(winning_card)))
    my_nums = set(map(int, numbers_pattern.findall(my_card)))

    count = len(winning_nums.intersection(my_nums))
    if count:
        sum_points += 2 ** (count - 1)

print(sum_points)
