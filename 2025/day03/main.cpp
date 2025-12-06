#include "solution.hpp"

int main() {

  auto testData = std::array<int, 15>{1,8,7,6,5,4,3,2,1,1,1,1,1,1,9};

  auto result = calculateJoltage(testData);

  return 0;
}