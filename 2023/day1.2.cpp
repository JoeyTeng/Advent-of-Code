// https://adventofcode.com/2023/day/1
#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <tuple>

constexpr std::array words{"",     "one", "two",   "three", "four",
                           "five", "six", "seven", "eight", "nine"};

int main() {
  uint64_t sum = 0;
  std::string line;
  while (std::getline(std::cin, line)) {
    auto first_digit_and_pos =
        std::make_tuple<int, std::string::size_type>(0, line.size());
    auto last_digit_and_pos =
        std::make_tuple<int, std::string::size_type>(0, 0);
    for (int i = 1; i <= 9; ++i) {
      auto pos = line.find(i + '0');
      if (pos != std::string::npos && pos <= std::get<1>(first_digit_and_pos)) {
        first_digit_and_pos = std::make_tuple(i, pos);
      }
      pos = line.find(words[i]);
      if (pos != std::string::npos && pos <= std::get<1>(first_digit_and_pos)) {
        first_digit_and_pos = std::make_tuple(i, pos);
      }

      pos = line.rfind(i + '0');
      if (pos != std::string::npos && pos >= std::get<1>(last_digit_and_pos)) {
        last_digit_and_pos = std::make_tuple(i, pos);
      }
      pos = line.rfind(words[i]);
      if (pos != std::string::npos && pos >= std::get<1>(last_digit_and_pos)) {
        last_digit_and_pos = std::make_tuple(i, pos);
      }
    }

    sum +=
        std::get<0>(first_digit_and_pos) * 10 + std::get<0>(last_digit_and_pos);
  }

  std::cout << sum << std::endl;

  return 0;
}
