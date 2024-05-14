#include "controller.hpp"

namespace kc {

std::unique_ptr<Controller> Controller::Instance(new Controller);

Controller::Controller()
    : m_logger(Utility::CreateLogger("controller"))
    , m_fanOn(false)
    , m_turnOnTime(0)
{
    wiringPiSetupGpio();
}

void Controller::controllerLoop(const Config::Pointer& config)
{
    pinMode(config->controlPin(), OUTPUT);
    digitalWrite(config->controlPin(), LOW);

    while (true)
    {
        double cpuTemperature = Utility::GetCpuTemperature();
        if (cpuTemperature > config->maxTemperature() && !m_fanOn)
        {
            /*
            *   The fan needs maximum amount of power when it starts spinning.
            *   Not a problem for powerful 12v fans, but cheap 5v fans may not start.
            *   The problem gets worse if the fan was still for months.
            *   Power surges or "pumping" will ensure the fan starts successfully.
            */
            for (int iteration = 0; iteration < config->pumpingCycles(); ++iteration)
            {
                digitalWrite(config->controlPin(), LOW);
                Utility::Sleep(0.001);
                digitalWrite(config->controlPin(), HIGH);
                Utility::Sleep(0.001);
            }
            m_fanOn = true;
            m_turnOnTime = std::time(nullptr);

            m_logger.info(
                "Fan turned on: CPU temperature is {:.1f}/{:.1f} 'C",
                cpuTemperature,
                static_cast<double>(config->maxTemperature())
            );
        }
        else if (cpuTemperature < config->minTemperature() && m_fanOn)
        {
            digitalWrite(config->controlPin(), LOW);
            m_fanOn = false;

            std::time_t totalElapsedSeconds = std::time(nullptr) - m_turnOnTime;
            std::time_t elapsedMinutes = totalElapsedSeconds / 60;
            std::time_t elapsedSeconds = totalElapsedSeconds - elapsedMinutes * 60;

            m_logger.info(
                "Fan turned off: CPU temperature is {:.1f}/{:.1f} 'C. Worked for {} minute{}, {} second{}",
                cpuTemperature,
                static_cast<double>(config->minTemperature()),
                elapsedMinutes, (elapsedMinutes == 1 ? "" : "s"),
                elapsedSeconds, (elapsedSeconds == 1 ? "" : "s")
            );
        }

        Utility::Sleep(config->checkInterval());
    }
}

} // namespace kc
