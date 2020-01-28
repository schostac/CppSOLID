find_package(Boost COMPONENTS system REQUIRED)

project(server)

set(SOURCE 
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/external/tinyxml2/tinyxml2.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} ${Boost_SYSTEM_LIBRARY})