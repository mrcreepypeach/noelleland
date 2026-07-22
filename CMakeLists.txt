cmake_minimum_required(VERSION 3.16)

project(noelleland)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib REQUIRED)

add_executable(noelleland
    src/main.cpp
    src/gameState.cpp
    src/settings.cpp
    src/noelle.cpp
)

target_include_directories(noelleland PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(noelleland PRIVATE raylib)