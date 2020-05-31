cmake_minimum_required(VERSION 3.10)

project(Auth)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCE
    ${PROJECT_SOURCE_DIR}/include/auth/IAuthentication.hpp
    ${PROJECT_SOURCE_DIR}/include/auth/IAuthorization.hpp
    ${PROJECT_SOURCE_DIR}/include/auth/AuthManager.hpp
    ${PROJECT_SOURCE_DIR}/src/AuthManager.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE})

target_link_libraries(${PROJECT_NAME} Common)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
