project(External)

set(SOURCE 
    ${PROJECT_SOURCE_DIR}/tinyxml2/tinyxml2.h
    ${PROJECT_SOURCE_DIR}/tinyxml2/tinyxml2.cpp
    ${PROJECT_SOURCE_DIR}/nlohmann/json.hpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE})

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR})
