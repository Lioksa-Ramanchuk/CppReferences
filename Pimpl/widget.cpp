#include "widget.hpp"

#include <numeric>
#include <shared_mutex>
#include <vector>

namespace pimpl {

struct Widget::Impl {
  std::vector<int> data{1, 2, 3, 4, 5};
  // ...
};

Widget::Widget() : pImpl_(std::make_unique<Impl>()) {}

Widget::Widget(const Widget& rhs) : pImpl_(nullptr) {
  std::shared_lock lock(rhs.mutex_);
  if (rhs.pImpl_) {
    pImpl_ = std::make_unique<Impl>(*rhs.pImpl_);
  }
}

Widget::Widget(Widget&& rhs) noexcept : pImpl_(nullptr) {
  std::unique_lock lock(rhs.mutex_);
  pImpl_ = std::exchange(rhs.pImpl_, nullptr);
}

Widget& Widget::operator=(const Widget& rhs) {
  if (this != &rhs) {
    std::unique_lock lock1(mutex_, std::defer_lock);
    std::shared_lock lock2(rhs.mutex_, std::defer_lock);
    std::lock(lock1, lock2);
    if (!rhs.pImpl_) {
      pImpl_.reset();
    } else if (!pImpl_) {
      pImpl_ = std::make_unique<Impl>(*rhs.pImpl_);
    } else {
      *pImpl_ = *rhs.pImpl_;
    }
  }
  return *this;
}

Widget& Widget::operator=(Widget&& rhs) noexcept {
  if (this != &rhs) {
    std::scoped_lock lock(mutex_, rhs.mutex_);
    pImpl_ = std::exchange(rhs.pImpl_, nullptr);
  }
  return *this;
}

Widget::~Widget() = default;

int Widget::GetDataSum() const {
  std::shared_lock lock(mutex_);
  return std::accumulate(pImpl_->data.cbegin(), pImpl_->data.cend(), 0);
}

}  // namespace pimpl