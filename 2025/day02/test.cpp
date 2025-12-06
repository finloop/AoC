#include "solution.hpp"
#include "../../catch_amalgamated.hpp"

TEST_CASE("part 2.1 works") {
  const char *data =
      "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,"
      "1698522-1698528,446443-446449,38593856-38593862,565653-"
      "565659,824824821-824824827,2121212118-2121212124";
  const auto parsed_data = parseData(data);

  auto result = std::transform_reduce(
      parsed_data.begin(), parsed_data.end(), 0LL, std::plus{},
      [](auto val) { return validateRange(val, validate_2); });

  REQUIRE(result == 4174379265);
}

TEST_CASE("part 2.2 works") {

  const auto parsed_data = parseData(data2);

  auto result = std::transform_reduce(
      parsed_data.begin(), parsed_data.end(), 0LL, std::plus{},
      [](auto val) { return validateRange(val, validate_2); });

  REQUIRE(result == 69564213293);
}
