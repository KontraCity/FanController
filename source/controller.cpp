#include "controller.hpp"

namespace kc {

std::unique_ptr<Controller> Controller::Instance(new Controller);

Controller::Controller()
    : m_fanOn(false)
    , m_turnOnTime(0)
{
    wiringPiSetupGpio();
}

void Controller::controllerLoop(const std::shared_ptr<Config>& config)
{
    m_config = config;
    pinMode(m_config->controlPin(), OUTPUT);
    digitalWrite(m_config->controlPin(), LOW);

    while (true)
    {
        double cpuTemperature = Utility::GetCpuTemperature();
        if (cpuTemperature > m_config->maxTemperature() && !m_fanOn)
        {
            /*
            *   Fan needs maximum amount of power when it starts spinning.
            *   Not a problem for powerful 12v fans, but cheap 5v fans may not start.
            *   Power surges or "pumping" will ensure the fan starts successfully.
            */
            for (int iteration = 0; iteration < 100; ++iteration)
            {
                digitalWrite(m_config->controlPin(), LOW);
                Utility::Sleep(0.001);
                digitalWrite(m_config->controlPin(), HIGH);
                Utility::Sleep(0.001);
            }
            m_fanOn = true;
            m_turnOnTime = std::time(nullptr);

            spdlog::info(
                "Fan turned on: CPU temperature is {0:.1f}/{1:.1f} 'C.",
                cpuTemperature,
                static_cast<double>(m_config->maxTemperature())
            );
        }
        else if (cpuTemperature < m_config->minTemperature() && m_fanOn)
        {
            digitalWrite(m_config->controlPin(), LOW);
            m_fanOn = false;

            std::time_t totalElapsedSeconds = std::time(nullptr) - m_turnOnTime;
            std::time_t elapsedMinutes = totalElapsedSeconds / 60;
            std::time_t elapsedSeconds = totalElapsedSeconds - elapsedMinutes * 60;

            spdlog::info(
                "Fan turned off: CPU temperature is {0:.1f}/{1:.1f} 'C. Worked for {2} minute{3}, {4} second{5}.",
                cpuTemperature,
                static_cast<double>(m_config->minTemperature()),
                elapsedMinutes, (elapsedMinutes == 1 ? "" : "s"),
                elapsedSeconds, (elapsedSeconds == 1 ? "" : "s")
            );
        }

        Utility::Sleep(m_config->checkInterval());
    }
}

} // namespace kc
