project(Auth)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(HEADERS
    ${PROJECT_SOURCE_DIR}/include/auth/AuthManager.hpp
)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/AuthManager.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Common
    Interfaces
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
