#include "console_logger.hpp"

#include <chrono>
#include <format>
#include <iostream>

namespace logger {

void ConsoleLogger::Log(std::string_view message) const noexcept {
  try {
    auto const time =
        std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
    std::cout << std::format("{:%d.%m.%Y %X} - {}\n", time, message);
  } catch (const std::exception& e) {
    std::cerr << std::format("Logging failed: {}\n", e.what());
  } catch (...) {
    std::cerr << "Logging failed with an unknown error.\n";
  }
}

}  // namespace logger