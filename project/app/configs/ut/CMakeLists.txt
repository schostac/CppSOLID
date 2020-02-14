project(ConfigsTests)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE StartupConfig_tests.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} GTest::GTest GTest::Main Configs)

add_test(${PROJECT_NAME} ${PROJECT_NAME})
