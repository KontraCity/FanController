// STL modules
#include <iostream>
#include <memory>

// Library spdlog
#include <spdlog/spdlog.h>

// Custom modules
#include "utility.hpp"
#include "config.hpp"
#include "controller.hpp"
using namespace kc;

int main(int parameterCount, char** parameterValue)
{
    for (int parameterIndex = 1; parameterIndex < parameterCount; ++parameterIndex)
    {
        std::string parameter = parameterValue[parameterIndex];
        if (parameter == "-h" || parameter == "--help")
        {
            std::cout << fmt::format(
                "Fan controller usage: {0} [OPTIONS]\n"
                "Available options:\n"
                "    (No options)\t\tStart fan controller normally\n"
                "    -h, --help\t\t\tDisplay this message and exit\n"
                "    -gc, --generate-config\tGenerate default config and exit\n",
                parameterValue[0]
            );
            return 0;
        }
        else if (parameter == "-gc" || parameter == "--generate-config")
        {
            try
            {
                Config::GenerateDefaultFile();
            }
            catch (const std::runtime_error& error)
            {
                std::cerr << fmt::format("Couldn't open configuration file \"{0}\"! Are you root?\n", ConfigConst::ConfigFilePath);
                return 1;
            }

            std::cout << fmt::format(
                "Generated default configuration file \"{0}\".\n"
                "Currently configured values:\n"
                "    Fan control pin\tGPIO {1}\n"
                "    Max temperature\t{2} 'C\n"
                "    Min temperature\t{3} 'C\n"
                "    Check interval\t{4}s\n",
                ConfigConst::ConfigFilePath,
                ConfigConst::Values::ControlPin::DefaultValue,
                ConfigConst::Values::MaxTemperature::DefaultValue,
                ConfigConst::Values::MinTemperature::DefaultValue,
                ConfigConst::Values::CheckInterval::DefaultValue
            );
            return 0;
        }
        else
        {
            std::cout << "Unknown option: " << parameter << '\n';
        }
    }

    std::shared_ptr<Config> config;
    try
    {
        config = std::make_shared<Config>();
    }
    catch (const Config::Error& error)
    {
        spdlog::critical("Configuration file parsing error: {0}.", error.what());
        spdlog::info("Check configuration file at \"{0}\".", ConfigConst::ConfigFilePath);
        spdlog::info("You can generate default configuration file by running \"{0} --generate-config\"", parameterValue[0]);
        return 1;
    }

    spdlog::info(
        "Ready. GPIO control pin: {0}, min temperature: {1:.1f} 'C, max: {2:.1f} 'C, checking every {3} second{4}.",
        config->controlPin(),
        static_cast<double>(config->minTemperature()),
        static_cast<double>(config->maxTemperature()),
        config->checkInterval(), (config->checkInterval() == 1 ? "" : "s")
    );

    try
    {
        kc::Controller::Instance->controllerLoop(config);
    }
    catch (const std::runtime_error& error)
    {
        spdlog::critical("Runtime error: {0}.", error.what());
        spdlog::critical("Fan controller is terminating.");
    }
}
