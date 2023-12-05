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

constexpr char NOT_SYMBOL = '.';

enum class State {
  NOT_VISITED,   // not yet detected
  IS_SYMBOL,     // is a symbol, not a digit
  MARKED_NUMBER, // should be counted for sum
  ADDED_NUMBER,  // already added for a sum
};

int main() {
  uint64_t sum = 0;

  std::vector<std::string> schematic;
  std::vector<std::vector<State>> states;
  std::string line;
  while (std::getline(std::cin, line)) {
    states.emplace_back(line.size(), State::NOT_VISITED);
    schematic.emplace_back(std::move(line));
  }

  // scan for symbol, then mark adjacent numbers
  for (size_t i = 0; i < schematic.size(); ++i) {
    for (size_t j = 0; j < schematic.front().size(); ++j) {
      const char ch = schematic[i][j];
      if (ch != NOT_SYMBOL && !std::isdigit(ch)) {
        states[i][j] = State::IS_SYMBOL;
        // detect adjacents
        for (size_t _i = (i >= 1) ? (i - 1) : i; // to ensure inbound
             _i <= std::min(i + 1, schematic.size() - 1); ++_i) {
          for (size_t _j = (j >= 1) ? (j - 1) : j; // to ensure inbound
               _j <= std::min(j + 1, schematic.front().size() - 1); ++_j) {
            if (std::isdigit(schematic[_i][_j])) {
              states[_i][_j] = State::MARKED_NUMBER;
            }
          }
        }
      }
    }
  }

  // scan for complete numbers and add them up
  for (size_t i = 0; i < schematic.size(); ++i) {
    for (size_t j = 0; j < schematic.front().size(); ++j) {
      if (states[i][j] == State::MARKED_NUMBER) {
        // scan back then scan forward
        signed int start_pos = j; // must be signed
        while (start_pos > 0 && std::isdigit(schematic[i][start_pos])) {
          states[i][start_pos] = State::ADDED_NUMBER;
          --start_pos;
        }
        assert(start_pos >= 0);
        if (!std::isdigit(schematic[i][start_pos])) {
          ++start_pos;
        }
        assert(std::isdigit(schematic[i][start_pos]));
        size_t end_pos = j + 1;
        while (end_pos < schematic.front().size() &&
               std::isdigit(schematic[i][end_pos])) {
          states[i][end_pos] = State::ADDED_NUMBER;
          ++end_pos;
        }
        // reach the end or something non-digit
        assert(end_pos >= schematic.front().size() ||
               !std::isdigit(schematic[i][end_pos]));
        int number = -1;
        std::istringstream ss(
            schematic[i].substr(start_pos, end_pos - start_pos));
        ss >> number;
        assert(number >= 0);
        sum += number;
      }
    }
  }

  std::cout << sum << std::endl;

  return 0;
}
