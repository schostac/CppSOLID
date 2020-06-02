project(Main)

add_executable(${PROJECT_NAME} Main.cpp)

target_link_libraries(${PROJECT_NAME} Configs Common Auth Parsers Services Servers)
