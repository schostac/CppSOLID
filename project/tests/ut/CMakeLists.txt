cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE 
    main.cpp
    dummy.cpp
)
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests ${SOURCE})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)