project(Configs)

add_subdirectory(ut)

find_package(Boost COMPONENTS program_options REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set(HEADERS
    ${PROJECT_SOURCE_DIR}/include/configs/StartupConfig.hpp
)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/StartupConfig.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    Common
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
