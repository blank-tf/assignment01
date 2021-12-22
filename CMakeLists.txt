cmake_minimum_required(VERSION 3.21)
project(assignment01)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

find_package(SFML COMPONENTS graphics audio window system REQUIRED)

add_executable(assignment01 src/main.cpp)
target_link_libraries(assignment01 sfml-graphics sfml-audio)