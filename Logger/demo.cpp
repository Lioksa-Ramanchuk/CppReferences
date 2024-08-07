#include "widget.hpp"
#include "console_logger.hpp"

int main() {
  using logger::Widget;
  using logger::ConsoleLogger;

  Widget w1;
  Widget::set_logger(std::make_shared<ConsoleLogger>());
  ++w1;
  --w1;
  return 0;
}