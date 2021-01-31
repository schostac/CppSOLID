cmake_minimum_required(VERSION 3.10)

project(plantcare)

SET(CMAKE_CXX_FLAGS "-std=c++17 -pthread -O3 -pedantic -Wall -Werror")

enable_testing()

add_subdirectory(sensors)
add_subdirectory(caretaker)
add_subdirectory(main)
