#include "widget.hpp"

namespace logger {

std::shared_ptr<ILogger> Widget::logger_ = nullptr;
std::shared_mutex Widget::logger_mutex_;

Widget::Widget(int initialValue) noexcept : value_(initialValue) {}

Widget& Widget::operator++() {
  std::unique_lock lock(mutex_);
  ++value_;
  Log("Value was incremented.");
  return *this;
}

Widget& Widget::operator--() {
  std::unique_lock lock(mutex_);
  --value_;
  Log("Value was decremented.");
  return *this;
}

int Widget::value() const { 
  std::shared_lock lock(mutex_);
  return value_;
}

void Widget::set_logger(std::shared_ptr<ILogger> logger) {
  std::unique_lock lock(logger_mutex_);
  logger_ = std::move(logger);
}

void Widget::Log(std::string_view message) noexcept {
  std::shared_lock lock(logger_mutex_);
  if (logger_) {
    logger_->Log(message);
  }
 }

}  // namespace logger