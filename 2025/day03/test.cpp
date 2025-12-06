#include "solution.hpp"
#include "../../catch_amalgamated.hpp"
#include <array>

TEST_CASE("test findFirstMax") {
  auto testData = std::array<int, 15>{9,8,7,6,5,4,3,2,1,1,1,1,1,1,1};

  REQUIRE(findFirstMax(testData).index ==  0);
  REQUIRE(findFirstMax(testData).number ==  9);
}

TEST_CASE("test findFirstMax 2") {
  auto testData = std::array<int, 15>{1,8,7,6,5,4,3,2,1,1,1,1,1,1,1};

  REQUIRE(findFirstMax(testData).index ==  1);
  REQUIRE(findFirstMax(testData).number ==  8);
}

TEST_CASE("Calculate joltage") {
  auto testData = std::array<int, 15>{1,8,7,6,5,4,3,2,1,1,1,1,1,1,1};

  REQUIRE(calculateJoltage(testData) == 87);
}

TEST_CASE("Calculate joltage 2") {
  auto testData = std::array<int, 15>{1,8,7,6,5,4,3,2,1,1,1,1,1,1,9};

  REQUIRE(calculateJoltage(testData) == 89);
}

TEST_CASE("Calculate joltage 3") {
  auto testData = std::array<int, 15>{1,8,7,6,5,4,3,2,1,1,1,1,1,9,1};

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

  REQUIRE(solve("input.txt") == 357); 

  REQUIRE(solve("part1.txt") == 17324);  
}


