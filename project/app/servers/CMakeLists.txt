project(Servers)

set(SOURCE
    ${PROJECT_SOURCE_DIR}/interfaces/services/ITaxServiceFactory.hpp
    ${PROJECT_SOURCE_DIR}/interfaces/services/ITaxService.hpp
    ${PROJECT_SOURCE_DIR}/include/servers/ReportSession.hpp
    ${PROJECT_SOURCE_DIR}/src/ReportSession.cpp
    ${PROJECT_SOURCE_DIR}/include/servers/Server.hpp
    ${PROJECT_SOURCE_DIR}/src/Server.cpp
)

find_package(Boost COMPONENTS system REQUIRED)

add_library(${PROJECT_NAME} STATIC ${SOURCE})

target_link_libraries(${PROJECT_NAME} ${Boost_SYSTEM_LIBRARY} Common Interfaces pthread)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/interfaces
)