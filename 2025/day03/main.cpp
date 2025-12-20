#include "solution.hpp"

int main() {
  auto result = calculateJoltageRecursive(parseLine("1111111121314151617181911111"), 12);
  std::println("Solution {}", result);  

  return 0;
}