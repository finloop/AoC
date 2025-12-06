#pragma once

#include <algorithm>
#include <cassert>
#include <charconv>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <numeric>
#include <print>
#include <ranges>
#include <string>
#include <vector>

const char *data = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,"
                   "1698522-1698528,446443-446449,38593856-38593862,565653-"
                   "565659,824824821-824824827,2121212118-2121212124";

const char *data2 =
    "824-1475,967620-1012917,2727216511-2727316897,56345-141494,8811120-"
    "8999774,5727326-5922513,935306-961989,76751455-76787170,723458-849157,"
    "144648-162230,1597-3207,326085-472746,14-34,66-132,9453977670-9454023729,"
    "959903262-960027272,17168-26699,190-332,3351-5602,1-11,371280315-"
    "371448887,6252062-6312899,9696887156-9697040132,37-58,32770-52161,"
    "6443650762-6443689882,473092-582157,3309726-3347079,852735-912990,"
    "8294840594-8294926063,3773964-3884030,7718304-7809359,601947-677833,"
    "3434304207-3434405118,449-673,64525269-64702774,31545468-31784543,184451-"
    "308951,5771-11485";

struct Range {
  int64_t start;
  int64_t end;
};

std::vector<Range> parseData(std::string_view data) {
  std::vector<Range> accumulator = {};
  size_t cursor = 0;
  int64_t first_match = 0;
  int64_t second_match = 0;
  for (size_t idx = 0; idx < data.length(); idx++) {
    if (data[idx] == '-') {
      // Parse the number
      std::string_view str = data.substr(cursor, idx - cursor + 1);
      std::from_chars(str.data(), str.data() + str.size(), first_match);
      cursor = idx + 1;
    } else if ((data[idx] == ',') || (idx == (data.length() - 1))) {
      // Parse the number
      std::string_view str = data.substr(cursor, idx - cursor + 1);
      std::from_chars(str.data(), str.data() + str.size(), second_match);
      cursor = idx + 1;

      accumulator.emplace_back(first_match, second_match);
    }
  }
  return accumulator;
}

bool validate_1(int64_t number) {
  auto num_as_string = std::to_string(number);
  if (num_as_string.length() % 2 == 1) {
    // All numbers of odd length cannot be symetric
    return false;
  }

  return !num_as_string.compare(
      0, num_as_string.length() / 2,
      num_as_string.substr(num_as_string.length() / 2, num_as_string.length()));
}

bool checkPatternOfLength(std::string_view data, size_t pattern_length) {
  if (pattern_length > data.length() / 2) {
    return false;
  }

  for (size_t idx = 0; idx < data.length(); idx += pattern_length) {
    if (!data.compare(0, pattern_length, data.substr(idx, pattern_length))) {
      continue;
    } else {
      return false;
    }
  }
  return true;
}

bool validate_2(int64_t number) {
  auto num_as_string = std::to_string(number);
  int max_pattern_length = num_as_string.length() / 2 + 1;
  auto pattern_lengths_to_check = std::ranges::iota_view{1, max_pattern_length};
  return std::any_of(pattern_lengths_to_check.begin(),
                     pattern_lengths_to_check.end(),
                     [&num_as_string](auto value) {
                       return checkPatternOfLength(num_as_string, value);
                     });
}

int64_t validateRange(const Range &range,
                      std::function<bool(int64_t)> validate) {
  auto numbers_in_range = std::ranges::iota_view{range.start, range.end + 1};
  return std::transform_reduce(numbers_in_range.begin(), numbers_in_range.end(),
                               0LL, std::plus{}, [validate](auto val) {
                                 if (validate(val)) {
                                   std::println("Match {}", val);
                                   return val;
                                 }
                                 return 0LL;
                                 // return validate(val) ? val : 0;
                               });
}