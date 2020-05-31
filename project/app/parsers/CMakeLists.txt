cmake_minimum_required(VERSION 3.10)

project(Parsers)

add_subdirectory(ut)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCE
    ${PROJECT_SOURCE_DIR}/include/parsers/IParsersFactory.hpp
    ${PROJECT_SOURCE_DIR}/include/parsers/ICredentialsParser.hpp
    ${PROJECT_SOURCE_DIR}/include/parsers/IReportParser.hpp
    ${PROJECT_SOURCE_DIR}/include/parsers/ParsersFactory.hpp
    ${PROJECT_SOURCE_DIR}/include/parsers/JsonParser.hpp
    ${PROJECT_SOURCE_DIR}/include/parsers/XmlParser.hpp
    ${PROJECT_SOURCE_DIR}/include/parsers/ValidatedReportParser.hpp
    ${PROJECT_SOURCE_DIR}/src/ParsersFactory.cpp
    ${PROJECT_SOURCE_DIR}/src/XmlParser.cpp
    ${PROJECT_SOURCE_DIR}/src/JsonParser.cpp
    ${PROJECT_SOURCE_DIR}/src/ValidatedReportParser.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE})

target_link_libraries(${PROJECT_NAME} Common External)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
