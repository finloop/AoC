#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <charconv>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <format>
#include <fstream>
#include <functional>
#include <numeric>
#include <print>
#include <ranges>
#include <span>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

struct ResultFindFirstMax {
  size_t index;
  int number;
};

ResultFindFirstMax findFirstMax(std::span<const int> array) {
  size_t max_idx = 0;
  for (size_t idx = 0; idx < array.size(); idx++) {
    if (array[idx] > array[max_idx]) {
      max_idx = idx;
    }
  }
  return {max_idx, array[max_idx]};
}

int calculateJoltage(std::span<const int> battery) {
  auto firstMax = findFirstMax(battery);

  // If the max is the last idx
  if (firstMax.index == battery.size() - 1) {
    auto secondMax2 = findFirstMax(battery.subspan(0, battery.size() - 1));

    return secondMax2.number * 10 + firstMax.number;
  }

  auto secondMax = findFirstMax(
      battery.subspan(firstMax.index + 1, battery.size() - firstMax.index));
  return firstMax.number * 10 + secondMax.number;
}

std::string buildJoltage(std::span<const int> battery, int remaindingElements) {
  if (remaindingElements == 1) {
    return std::format("{}", findFirstMax(battery).number);
  }

  // Find the max value in the part of the subspan
  // that is at least size of level

  // 7 - 2 = 5
  // 0 1 2 3 4 5 6
  // + + + + + + x
  // 1
  // 1
  int numberOfElementsOnLeft = battery.size() - remaindingElements + 1;

  // We found the max value and we can "fit"
  // That means that our solution must be on the "right"
  // current max will be part of the solution
  auto maxValue = findFirstMax(battery.subspan(0, numberOfElementsOnLeft));
  int numberOfElementsOnRight = battery.size() - maxValue.index - 1;

  return std::format("{}", maxValue.number) +
         buildJoltage(
             battery.subspan(maxValue.index + 1, numberOfElementsOnRight),
             remaindingElements - 1);
}

int64_t calculateJoltageRecursive(std::span<const int> battery, int length) {
  auto result = buildJoltage(battery, length);
  int64_t out = 0;
  char *end;
  out = std::strtoll(result.c_str(), &end, 10);

  const bool range_error = errno == ERANGE;

  return out;
}

std::vector<int> parseLine(std::string_view line) {
  auto result = std::vector<int>(line.size());
  for (size_t idx = 0; idx < line.size(); idx++) {
    // HACK:
    // https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
    result[idx] = line.at(idx) - '0';
  }
  return result;
}

std::vector<std::vector<int>> loadData(std::string_view filename) {
  std::vector<std::vector<int>> loadedData{};
  std::string line;
  std::ifstream myfile(filename.data());
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      loadedData.emplace_back(parseLine(line));
    }
    myfile.close();
  }
  return loadedData;
}

int solve(std::string_view filename) {
  auto loadedData = loadData(filename);
  return std::transform_reduce(loadedData.begin(), loadedData.end(), 0LL,
                               std::plus{},
                               [](auto val) { return calculateJoltage(val); });
}

int64_t solve_recursive(std::string_view filename, int level) {
  auto loadedData = loadData(filename);
  return std::transform_reduce(loadedData.begin(), loadedData.end(), 0LL,
                               std::plus{}, [level](auto val) {
                                 auto result =
                                     calculateJoltageRecursive(val, level);
                                 return result;
                               });
}