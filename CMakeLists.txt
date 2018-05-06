cmake_minimum_required(VERSION 3.10)
project(lab2)

set(CMAKE_CXX_STANDARD 11)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(lab2 main.cpp license.h date.h container.h table.h)
target_link_libraries(lab2 ${CURSES_LIBRARIES})
target_link_libraries(lab2 menu)
