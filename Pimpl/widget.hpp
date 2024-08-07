#ifndef PIMPL_WIDGET_HPP
#define PIMPL_WIDGET_HPP

#include <shared_mutex>

namespace pimpl {

class Widget {
 public:
  explicit Widget();
  Widget(const Widget& rhs);
  Widget(Widget&& rhs) noexcept;
  Widget& operator=(const Widget& rhs);
  Widget& operator=(Widget&& rhs) noexcept;
  ~Widget();

  int GetDataSum() const;

 private:
  struct Impl;

  mutable std::shared_mutex mutex_;
  std::unique_ptr<Impl> pImpl_;
};

}  // namespace pimpl

#endif  // !PIMPL_WIDGET_HPP