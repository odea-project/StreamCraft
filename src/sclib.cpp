#include "sclib.hpp"
#include <iostream>

void sc::welcome() {
  std::cout << std::endl;
  // make a welcome message with Stream in dark blue and Craft is red but glue the words together as StreamCraft
  std::cout << "  \033[1;34mStream\033[0m\033[1;31mCraft\033[0m" << std::endl;
  std::cout << std::endl;
};
