project(ServicesTests)

find_package(GTest REQUIRED)

include_directories(
    ${GTEST_INCLUDE_DIRS}
    ${GMOCK_INCLUDE_DIRS}
)

set(SOURCES
    TaxService_tests.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    GTest::GTest
    GTest::Main
    gmock
    gmock_main
    Interfaces
    Servers
    Mocks
    Services
    Storage
    Common
)

add_test(${PROJECT_NAME} ${PROJECT_NAME})