## --- Project configuration --- ##
cmake_minimum_required(VERSION 3.10)
project(FanController VERSION 1.1)

## --- Compiler configuration --- ##
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories("include/")

## --- Executable configuration --- ##
add_executable(FanController
    "source/config.cpp"
    "source/controller.cpp"
    "source/main.cpp"
    "source/utility.cpp"
)
target_link_libraries(FanController
    "fmt"
    "wiringPi"
)
