#ifndef THE_RULE_OF_FIVE_WIDGET_HPP
#define THE_RULE_OF_FIVE_WIDGET_HPP

#include <optional>
#include <shared_mutex>

namespace the_rule_of_five {

class Widget {
 public:
  explicit Widget(int data = 0);
  Widget(const Widget& rhs);
  Widget(Widget&& rhs) noexcept;
  Widget& operator=(const Widget& rhs);
  Widget& operator=(Widget&& rhs) noexcept;
  ~Widget();

  std::optional<int> data() const;

  void set_data(const int& data);
  void set_data(int&& data);

 private:
  template <typename T>
  void set_data_impl(T&& data)
    requires std::same_as<std::decay_t<T>, int>;

  mutable std::shared_mutex mutex_;
  int* data_;
};

}  // namespace the_rule_of_five

#include "widget.ipp"

#endif  // !THE_RULE_OF_FIVE_WIDGET_HPP