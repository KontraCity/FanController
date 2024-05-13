#pragma once

// STL modules
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>

// Library {fmt}
#include <fmt/format.h>

namespace kc {

namespace ConfigConst
{
    // Controller configuration file path
    constexpr const char* ConfigFile = "/etc/fancontroller.conf";

    namespace Values
    {
        namespace ControlPin
        {
            constexpr const char* Tag = "ControlPin";
            constexpr unsigned int DefaultValue = 14;
        }

        namespace MaxTemperature
        {
            constexpr const char* Tag = "MaxTemperature";
            constexpr unsigned int DefaultValue = 70;
        }

        namespace MinTemperature
        {
            constexpr const char* Tag = "MinTemperature";
            constexpr unsigned int DefaultValue = 50;
        }

        namespace CheckInterval
        {
            constexpr const char* Tag = "CheckInterval";
            constexpr unsigned int DefaultValue = 10;
        }
    }
}

class Config
{
public:
    // Shared config instance pointer
    using Pointer = std::shared_ptr<Config>;

    // Configuration file read/parse error
    class Error : public std::logic_error
    {
    public:
        using logic_error::logic_error;
    };

private:
    int m_controlPin;
    int m_maxTemperature;
    int m_minTemperature;
    int m_checkInterval;

public:
    /// @brief Generate sample configuration file
    /// @throw std::runtime_error if file couldn't be created
    static void GenerateSampleFile();

public:
    /// @brief Read and parse configuration file
    /// @throw Config::Error if reading/parsing error occurs
    Config();

    /// @brief Get fan control pin
    /// @return Fan control pin
    inline int controlPin() const
    {
        return m_controlPin;
    }

    /// @brief Get max temperature at which fan turns on
    /// @return Max temperature at which fan turns on
    inline int maxTemperature() const
    {
        return m_maxTemperature;
    }

    /// @brief Get min temperature at which fan turns off
    /// @return Get min temperature at which fan turns off
    inline int minTemperature() const
    {
        return m_minTemperature;
    }

    /// @brief Get CPU temperature check interval in seconds
    /// @return CPU temperature check interval in seconds
    inline int checkInterval() const
    {
        return m_checkInterval;
    }
};

} // namespace kc
