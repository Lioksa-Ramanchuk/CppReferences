#include <format>
#include <iostream>
#include "widget.hpp"

int main() {
  using pimpl::Widget;
  Widget w1;
  std::cout << std::format("Sum of w1 data elements: {}\n", w1.GetDataSum());
  return 0;
}