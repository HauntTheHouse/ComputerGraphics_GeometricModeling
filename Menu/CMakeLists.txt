cmake_minimum_required(VERSION 3.0.0)

project(Menu)

find_package(SFML COMPONENTS system window graphics)
find_package(TGUI)

add_library(${PROJECT_NAME} Menu.h Menu.cpp CustomPanel.h CustomPanel.cpp)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system tgui)
