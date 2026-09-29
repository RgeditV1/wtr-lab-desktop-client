cmake_minimum_required(VERSION 3.20)
project(wtr_lab_client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
)

add_executable(wtr_lab_client
    src/main.cpp
)

target_link_libraries(wtr_lab_client PRIVATE
    fmt::fmt
    spdlog::spdlog
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)