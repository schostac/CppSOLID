project(ServicesTests)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE 
    TaxService_tests.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} GTest::GTest GTest::Main gmock Mocks Services Auth External Common)

add_test(${PROJECT_NAME} ${PROJECT_NAME})