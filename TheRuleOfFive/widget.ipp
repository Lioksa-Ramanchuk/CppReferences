#ifndef THE_RULE_OF_FIVE_WIDGET_HPP
#error "This file should be included only through widget.hpp."
#endif

namespace the_rule_of_five {

template <typename T>
void Widget::set_data_impl(T&& data)
  requires std::same_as<std::decay_t<T>, int>
{
  std::unique_lock lock(mutex_);
  if (data_) {
    delete data_;
  }
  data_ = new int(std::forward<T>(data));
}

}  // namespace the_rule_of_five