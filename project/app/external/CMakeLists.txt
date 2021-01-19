project(External)

set(HEADERS
    ${PROJECT_SOURCE_DIR}/nlohmann/json.hpp
    ${PROJECT_SOURCE_DIR}/tinyxml2/tinyxml2.h
)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/tinyxml2/tinyxml2.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR})
