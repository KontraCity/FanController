### --- Initial configuration --- ###
cmake_minimum_required(VERSION 3.10)
project(FanController VERSION 1.1)

# Set CXX version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


### --- Executable configuration --- ### 
add_executable(FanController
    "source/config.cpp"
    "source/controller.cpp"
    "source/main.cpp"
    "source/utility.cpp"
)
target_include_directories(FanController PRIVATE "include/")


### --- Libraries configuration --- ###
target_link_libraries(FanController
    "fmt"
    "wiringPi"
)

# Library spdlog
find_package(spdlog REQUIRED)
target_link_libraries(FanController spdlog::spdlog)
