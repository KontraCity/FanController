#include "utility.hpp"

namespace kc {

double Utility::GetCpuTemperature()
{
    std::ifstream temperatureFile("/sys/class/thermal/thermal_zone0/temp");
    if (!temperatureFile)
        throw std::runtime_error("kc::Utility::GetCpuTemperature(): Couldn't open temperature file");

    double temperature;
    temperatureFile >> temperature;

    /*
    *   Temperature in the file is stored as an integer 1000 times higher than actual temperature.
    *   Example: Stored 56230, actual 56.23'C.
    *   This is why temperature number is divided by 1000.
    */
    return temperature / 1000;
}

void Utility::Sleep(double seconds)
{
    std::this_thread::sleep_for(std::chrono::microseconds(static_cast<size_t>(seconds * 1'000'000)));
}

} // namespace kc
