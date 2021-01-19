project(ConfigsTests)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCES StartupConfig_tests.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    GTest::GTest
    GTest::Main
    Configs
    Common
)

add_test(${PROJECT_NAME} ${PROJECT_NAME})
