project(Storage)

set(HEADERS
    ${PROJECT_SOURCE_DIR}/include/storage/ReportsStorage.hpp
)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/ReportsStorage.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE Common)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
