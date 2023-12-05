// https://adventofcode.com/2023/day/3
#include <cassert>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

constexpr char GEAR_SYMBOL = '*';

int num_of_numbers(std::string_view str) {
  int count = 0;
  bool reading_digit = false;
  for (char ch : str) {
    if (reading_digit != std::isdigit(ch)) {
      reading_digit = !reading_digit;
      count += reading_digit ? 1 : 0;
    }
  }

  return count;
}

int scan_and_return_number(std::string_view str, size_t pos) {
  // scan back then scan forward
  signed int start_pos = pos; // must be signed
  while (start_pos > 0 && std::isdigit(str[start_pos])) {
    --start_pos;
  }
  assert(start_pos >= 0);
  if (!std::isdigit(str[start_pos])) {
    ++start_pos;
  }
  assert(std::isdigit(str[start_pos]));

  size_t end_pos = pos + 1;
  while (end_pos < str.size() && std::isdigit(str[end_pos])) {
    ++end_pos;
  }
  // reach the end or something non-digit
  assert(end_pos >= str.size() || !std::isdigit(str[end_pos]));
  int number = -1;
  std::string _str(str.substr(start_pos, end_pos - start_pos));
  std::istringstream ss(_str);
  ss >> number;
  assert(number >= 0);

  return number;
}

int main() {
  uint64_t sum = 0;

  std::vector<std::string> schematic;
  std::string line;
  while (std::getline(std::cin, line)) {
    schematic.emplace_back(std::move(line));
  }

  // scan for symbol, then mark adjacent numbers
  for (size_t i = 0; i < schematic.size(); ++i) {
    for (size_t j = 0; j < schematic.front().size(); ++j) {
      const char ch = schematic[i][j];
      if (ch == GEAR_SYMBOL) {
        // detect adjacents
        int adj_numbers[3] = {0};
        int min_delta = (i >= 1) ? -1 : 0;
        int max_delta = (i + 1 < schematic.size()) ? 1 : 0;
        for (int delta = min_delta; delta <= max_delta; ++delta) {
          if (j > 1) {
            adj_numbers[1 + delta] +=
                num_of_numbers(schematic[i + delta].substr(j - 1, 3));
          } else {
            assert(j == 0);
            adj_numbers[1 + delta] +=
                num_of_numbers(schematic[i + delta].substr(j, 2));
          }
        }

        const int total_adj_numbers =
            adj_numbers[0] + adj_numbers[1] + adj_numbers[2];

        int sum_base = 1;
        if (total_adj_numbers == 2) {
          // is gear
          for (int _i = 0; _i < 3; ++_i) {
            switch (adj_numbers[_i]) {
            case 2:
              sum_base *= scan_and_return_number(schematic[i + _i - 1], j - 1) *
                          scan_and_return_number(schematic[i + _i - 1], j + 1);
              break;
            case 1:
              for (int _j = (j >= 1) ? j - 1 : j;
                   _j <= std::min(j + 1, schematic.front().size() - 1); ++_j) {
                if (std::isdigit(schematic[i + _i - 1][_j])) {
                  sum_base *= scan_and_return_number(schematic[i + _i - 1], _j);
                  break;
                }
              }
              break;
            case 0:
              break;
            default:
              assert(false);
            }
          }

          sum += sum_base;
        }
      }
    }
  }

  std::cout << sum << std::endl;

  return 0;
}
