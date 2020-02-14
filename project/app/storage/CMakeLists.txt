project(Storage)

set(SOURCE
    ${PROJECT_SOURCE_DIR}/include/storage/ReportsStorage.hpp
    ${PROJECT_SOURCE_DIR}/src/ReportsStorage.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE})

target_link_libraries(${PROJECT_NAME} Common)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)