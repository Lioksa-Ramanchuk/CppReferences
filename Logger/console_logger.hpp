#ifndef LOGGER_CONSOLE_LOGGER_HPP
#define LOGGER_CONSOLE_LOGGER_HPP

#include "i_logger.hpp"

namespace logger {

class ConsoleLogger : public ILogger {
 public:
  void Log(std::string_view message) const noexcept override;
};

}  // namespace logger

#endif  // !LOGGER_CONSOLE_LOGGER_HPP