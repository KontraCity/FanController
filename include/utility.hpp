#pragma once

// STL modules
#include <thread>
#include <chrono>
#include <fstream>
#include <stdexcept>

namespace kc {

namespace Utility
{
    /// @brief Get current CPU temperature in celcius degrees
    /// @throw std::runtime_error if internal error occurs
    /// @return Current CPU temperature in celcius degrees
    double GetCpuTemperature();

    /// @brief Stop execution for some time
    /// @param seconds Seconds to stop execution for
    void Sleep(double seconds);
}

} // namespace kc
