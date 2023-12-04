#pragma once

// STL modules
#include <ctime>
#include <memory>
#include <thread>
#include <stdexcept>

// Library WiringPi
#include <wiringPi.h>

// Library spdlog
#include <spdlog/spdlog.h>

// Custom modules
#include "config.hpp"
#include "utility.hpp"

namespace kc {

class Controller
{
private:
    bool m_fanOn;
    std::time_t m_turnOnTime;
    std::shared_ptr<Config> m_config;

public:
    // Singleton instance pointer
    static std::unique_ptr<Controller> Instance;

private:
    /// @brief Initialize fan controller
    Controller();

public:
    /// @brief Fan controller loop
    /// @param config Parsed fan controller config
    void controllerLoop(const std::shared_ptr<Config>& config);
};

} // namespace kc
