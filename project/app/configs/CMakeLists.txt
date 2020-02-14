project(Configs)

add_subdirectory(ut)

find_package(Boost COMPONENTS program_options REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME} INTERFACE ${Boost_LIBRARIES} Common)

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include)
