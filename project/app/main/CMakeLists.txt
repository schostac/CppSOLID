project(Main)

add_executable(${PROJECT_NAME} Main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Interfaces
    Servers
    Services
    Configs
    Common
    Auth
    Parsers
)
