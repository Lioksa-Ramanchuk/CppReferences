#include "widget.hpp"
#include <optional>
#include <shared_mutex>
#include <utility>

namespace the_rule_of_five {

Widget::Widget(int data) : data_(new int(data)) {}

Widget::Widget(const Widget& rhs) : data_(nullptr) {
  std::shared_lock lock(rhs.mutex_);
  if (rhs.data_) {
    data_ = new int(*rhs.data_);
  }
}

Widget::Widget(Widget&& rhs) noexcept : data_(nullptr) {
  std::unique_lock lock(rhs.mutex_);
  data_ = std::exchange(rhs.data_, nullptr);
}

Widget& Widget::operator=(const Widget& rhs) {
  if (this != &rhs) {
    std::unique_lock lock1(mutex_, std::defer_lock);
    std::shared_lock lock2(rhs.mutex_, std::defer_lock);
    std::lock(lock1, lock2);
    if (data_) {
      delete data_;
      data_ = nullptr;
    }
    if (rhs.data_) {
      data_ = new int(*rhs.data_);
    }
  }
  return *this;
}

Widget& Widget::operator=(Widget&& rhs) noexcept {
  if (this != &rhs) {
    std::scoped_lock lock(mutex_, rhs.mutex_);
    if (data_) {
      delete data_;
    }
    data_ = std::exchange(rhs.data_, nullptr);
  }
  return *this;
}

Widget::~Widget() {
  if (data_) {
    delete data_;
  }
}

std::optional<int> Widget::data() const {
  std::shared_lock lock(mutex_);
  return data_ ? std::optional<int>{*data_} : std::nullopt;
}

void Widget::set_data(const int& data) { set_data_impl(data); }
void Widget::set_data(int&& data) { set_data_impl(std::move(data)); }

}  // namespace the_rule_of_five