cmake_minimum_required(VERSION 3.10)

project(Services)

add_subdirectory(ut)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCE 
    ${PROJECT_SOURCE_DIR}/include/services/TaxService.hpp
    ${PROJECT_SOURCE_DIR}/src/TaxServiceFactory.cpp
    ${PROJECT_SOURCE_DIR}/src/TaxService.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE})

target_link_libraries(${PROJECT_NAME} Common Interfaces Servers Storage)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
