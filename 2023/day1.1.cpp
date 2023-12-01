// https://adventofcode.com/2023/day/1
#include <cstdint>
#include <iostream>
#include <string>

int main() {
  uint64_t sum = 0;
  std::string line;
  while (std::getline(std::cin, line)) {
    char last_digit = 0;
    for (auto ch : line) {
      if ('0' <= ch && ch <= '9') {
        if (!last_digit) {
          // not finding any digit yet.
          sum += (ch - '0') * 10;
        }
        last_digit = ch;
      }
    }
    sum += last_digit - '0';
  }

  std::cout << sum << std::endl;

  return 0;
}
