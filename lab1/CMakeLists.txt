cmake_minimum_required(VERSION 3.0.0)

project(lab1)

set(SRC_DIR "src/")
set(FONTS_DIR "fonts/")

file(GLOB SRC_LIST CONFIGURE_DEPENDS
    ${SRC_DIR}*.h
    ${SRC_DIR}*.cpp
)

file(GLOB FONTS_LIST
    ${FONTS_DIR}*.ttf
)

foreach(FONT ${FONTS_LIST})
    string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" FONT_FILE ${FONT})
    message("Copy to build directory: ${FONT_FILE}")
    configure_file(${FONT_FILE} ${FONT_FILE} COPYONLY)
endforeach()

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system tgui)
