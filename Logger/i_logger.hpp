#ifndef LOGGER_I_LOGGER_HPP
#define LOGGER_I_LOGGER_HPP

#include <string_view>

namespace logger {

class ILogger {
 public:
  virtual ~ILogger() = default;
  virtual void Log(std::string_view message) const noexcept = 0;
};

}  // namespace logger

#endif  // !LOGGER_I_LOGGER_HPP