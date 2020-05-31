project(Main)

find_package(Boost COMPONENTS program_options REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} Main.cpp)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} Configs Common Auth Parsers Services Servers)
