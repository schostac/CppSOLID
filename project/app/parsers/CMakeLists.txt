cmake_minimum_required(VERSION 3.10)

project(Parsers)

add_subdirectory(ut)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCE
    ${PROJECT_SOURCE_DIR}/include/parsers/IReportParser.hpp
    ${PROJECT_SOURCE_DIR}/include/parsers/JsonReportParser.hpp
    ${PROJECT_SOURCE_DIR}/include/parsers/XmlReportParser.hpp
    ${PROJECT_SOURCE_DIR}/include/parsers/ValidatedReportParser.hpp
    ${PROJECT_SOURCE_DIR}/src/XmlReportParser.cpp
    ${PROJECT_SOURCE_DIR}/src/JsonReportParser.cpp
    ${PROJECT_SOURCE_DIR}/src/ValidatedReportParser.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE})

target_link_libraries(${PROJECT_NAME} Common External)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
