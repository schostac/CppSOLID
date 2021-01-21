cmake_minimum_required(VERSION 3.10)

project(server)

set(CMAKE_CXX_FLAGS "-std=c++17 -O3 -pedantic -Wall -Werror")

enable_testing()

add_subdirectory(external)
add_subdirectory(interfaces)
add_subdirectory(common)
add_subdirectory(configs)
add_subdirectory(servers)
add_subdirectory(services)
add_subdirectory(parsers)
add_subdirectory(storage)
add_subdirectory(auth)
add_subdirectory(main)
add_subdirectory(mocks)
