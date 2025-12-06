#include <cassert>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

const int g_DIAL_MAX_VAL = 100;

enum Direction { Left, Right };

struct Rotation {
  Direction dir;
  int clicks;
};

static int counter = 0;

int modulo(int number, int modulus) {
  if (number >= modulus) {
    return modulo(number - modulus, modulus);
  } else if (number < 0) {
    return modulo(number + modulus, modulus);
  }
  return number;
}

int rotate(int current_position, const Rotation rotation) {
  
  // Range from 0 to g_DIAL_MAX_VAL
  int position = current_position;
  switch (rotation.dir) {
  case Direction::Left:
    position = (current_position - rotation.clicks);
    if (position <= 0 && current_position > 0) {
        counter++;
    }
    break;
  case Direction::Right:
    position = (current_position + rotation.clicks);
    break;
  }
  counter += std::abs(position) / g_DIAL_MAX_VAL;

  return modulo(position, g_DIAL_MAX_VAL);
}

int main() {
  std::string line;
  std::ifstream myfile("input.txt");
  int current_position = 50;
  if (myfile.is_open()) {
    while (getline(myfile, line)) {

      assert(line.length() > 1 && "Wrong input");
      const Direction d =
          line.rfind("L") == 0 ? Direction::Left : Direction::Right;
      const int clicks = atoi(line.substr(1, line.length()).c_str());

      current_position = rotate(current_position, {d, clicks});
      std::cout << "Line " << line << " pos " << current_position << " counter " << counter  <<std::endl;
    }
    myfile.close();

    std::cout << "Result " << counter << std::endl;
  }
  return 0;
}