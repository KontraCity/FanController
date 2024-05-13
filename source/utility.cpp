#include "utility.hpp"

namespace kc {

spdlog::logger Utility::CreateLogger(const std::string& name, std::optional<bool> forceColor)
{
    static auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    if (forceColor)
    {
        /*
        *   This function is initialized when forceColor argument is passed.
        *   This is why the sink is configured here.
        */
        sink->set_pattern("[%^%d.%m.%C %H:%M:%S%$] [%n] %v");
        if (*forceColor)
            sink->set_color_mode(spdlog::color_mode::always);
    }
    return { name, {sink} };
}

double Utility::GetCpuTemperature()
{
    std::ifstream temperatureFile("/sys/class/thermal/thermal_zone0/temp");
    if (!temperatureFile)
        throw std::runtime_error("kc::Utility::GetCpuTemperature(): Couldn't open temperature file");

    /*
    *   Temperature in the file is stored as an integer 1000 times higher than actual temperature.
    *   Example: Stored 56230, actual 56.23'C.
    *   This is why temperature number is divided by 1000.
    */
    double temperature;
    temperatureFile >> temperature;
    return temperature / 1000;
}

void Utility::Sleep(double seconds)
{
    std::this_thread::sleep_for(std::chrono::microseconds(static_cast<size_t>(seconds * 1'000'000)));
}

} // namespace kc
