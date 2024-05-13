#pragma once

// STL modules
#include <optional>
#include <thread>
#include <chrono>
#include <fstream>
#include <stdexcept>

// Library spdlog
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace kc {

namespace Utility
{
    /// @brief Create a logger
    /// @param name Logger name
    /// @param forceColor Whether to force sinks colors or not
    /// @return Created logger
    spdlog::logger CreateLogger(const std::string& name, std::optional<bool> forceColor = {});

    /// @brief Get current CPU temperature in celcius degrees
    /// @throw std::runtime_error if internal error occurs
    /// @return Current CPU temperature in celcius degrees
    double GetCpuTemperature();

    /// @brief Stop execution for some time
    /// @param seconds Seconds to stop execution for
    void Sleep(double seconds);
}

} // namespace kc
