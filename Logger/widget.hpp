#ifndef LOGGER_WIDGET_HPP
#define LOGGER_WIDGET_HPP

#include <memory>
#include <shared_mutex>

#include "i_logger.hpp"

namespace logger {

class Widget {
 public:
  explicit Widget(int initialValue = 0) noexcept;

  Widget& operator++();
  Widget& operator--();

  int value() const;

  static void set_logger(std::shared_ptr<ILogger> logger);

 private:
  static void Log(std::string_view message) noexcept;
   
  static std::shared_ptr<ILogger> logger_;
  static std::shared_mutex logger_mutex_;

  mutable std::shared_mutex mutex_;
  int value_;
};

}  // namespace logger

#endif  // !LOGGER_WIDGET_HPP