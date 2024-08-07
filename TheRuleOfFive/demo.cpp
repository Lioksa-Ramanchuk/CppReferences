#include <iostream>
#include <format>
#include "widget.hpp"

int main() {
  using the_rule_of_five::Widget;

  {
    Widget w1(42);
    std::cout << std::format("w1 data: {}\n", w1.data().value_or(-1));

    Widget w2(w1);
    std::cout << std::format("w2 (copy constructor from w1) data: {}\n",
                             w2.data().value_or(-1));

    Widget w3(std::move(w1));
    std::cout << std::format("w3 (move constructor from w1) data: {}\n",
                             w3.data().value_or(-1));

    Widget w4;
    w4 = w2;
    std::cout << std::format("w4 (copy assignment from w2) data: {}\n",
                             w4.data().value_or(-1));

    Widget w5;
    w5 = std::move(w2);
    std::cout << std::format("w5 (move assignment from w2) data: {}\n",
                             w5.data().value_or(-1));

    std::cout << "Destructors are called...";
  }
  std::cout << " now.\n";
  
  return 0;
}