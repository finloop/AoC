#include "../../catch_amalgamated.hpp"
#include "solution.hpp"
#include <array>

TEST_CASE("test findFirstMax") {
  auto testData =
      std::array<int, 15>{9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 1, 1};

  REQUIRE(findFirstMax(testData).index == 0);
  REQUIRE(findFirstMax(testData).number == 9);
}

TEST_CASE("test findFirstMax 2") {
  auto testData =
      std::array<int, 15>{1, 8, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 1, 1};

  REQUIRE(findFirstMax(testData).index == 1);
  REQUIRE(findFirstMax(testData).number == 8);
}

TEST_CASE("Calculate joltage") {
  auto testData =
      std::array<int, 15>{1, 8, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 1, 1};

  REQUIRE(calculateJoltage(testData) == 87);
}

TEST_CASE("Calculate joltage 2") {
  auto testData =
      std::array<int, 15>{1, 8, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 1, 9};

  REQUIRE(calculateJoltage(testData) == 89);
}

TEST_CASE("Calculate joltage 3") {
  auto testData =
      std::array<int, 15>{1, 8, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 9, 1};

  REQUIRE(calculateJoltage(testData) == 91);
}

TEST_CASE("Parse line") {

  REQUIRE(parseLine("123").at(1) == 2);
  REQUIRE(parseLine("123534253").at(0) == 1);
  REQUIRE(parseLine("123").at(2) == 3);
}

TEST_CASE("Part 1") {
  auto loadedData = loadData("input.txt");

  REQUIRE(loadedData.at(0).at(0) == 9);

  REQUIRE(solve("part1.txt") == 17324);
}

TEST_CASE("Part 1 with recursion") {
  auto loadedData = loadData("input.txt");

  REQUIRE(calculateJoltageRecursive(parseLine("987654321111111"), 2) == 98);
  REQUIRE(calculateJoltageRecursive(parseLine("811111111111119"), 2) == 89);
  REQUIRE(calculateJoltageRecursive(parseLine("234234234234278"), 2) == 78);
  REQUIRE(calculateJoltageRecursive(parseLine("818181911112111"), 2) == 92);
}

TEST_CASE("Part 2 with recursion") {
  REQUIRE(calculateJoltageRecursive(parseLine("987654321111111"), 12) ==
          987654321111LL);
  REQUIRE(calculateJoltageRecursive(parseLine("811111111111119"), 12) ==
          811111111119LL);
  REQUIRE(calculateJoltageRecursive(parseLine("234234234234278"), 12) ==
          434234234278LL);
  REQUIRE(calculateJoltageRecursive(parseLine("818181911112111"), 12) ==
          888911112111LL);
  REQUIRE(calculateJoltageRecursive(
              parseLine("312321399998811118891919191818181812"),
              12) == 999999998888LL);
  REQUIRE(calculateJoltageRecursive(
parseLine("1111111121314151617181911111"),
12) == 111123456789);
}

TEST_CASE("Part 2 with recusrion") {
  REQUIRE(solve_recursive("part2.txt", 12) == 0);
}
