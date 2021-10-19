cmake_minimum_required(VERSION 3.0.0)

project(CoordinateSystem)

find_package(SFML COMPONENTS system window graphics)
find_package(TGUI)

add_library(${PROJECT_NAME} CoordinateSystem.h CoordinateSystem.cpp)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system tgui)
