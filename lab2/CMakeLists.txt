cmake_minimum_required(VERSION 3.0.0)

project(lab2)

file(GLOB SRC_LIST CONFIGURE_DEPENDS
        *.h
        *.cpp
        )

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/menu)
target_link_libraries(${PROJECT_NAME} menu)
