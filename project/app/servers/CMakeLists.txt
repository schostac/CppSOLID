project(Servers)

find_package(Boost COMPONENTS system REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set(HEADERS
    ${PROJECT_SOURCE_DIR}/interfaces/services/ITaxServiceFactory.hpp
    ${PROJECT_SOURCE_DIR}/interfaces/services/ITaxService.hpp
    ${PROJECT_SOURCE_DIR}/include/servers/ReportSession.hpp
)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/ReportSession.cpp
    ${PROJECT_SOURCE_DIR}/include/servers/Server.hpp
    ${PROJECT_SOURCE_DIR}/src/Server.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

set(COMON_LINK_LIBS
    ${PROJECT_NAME}
    ${Boost_SYSTEM_LIBRARY}
    Common
    Interfaces
    pthread
)

if (WIN32)
    target_link_libraries(${COMON_LINK_LIBS} ws2_32)
else ()
    target_link_libraries(${COMON_LINK_LIBS})
endif (WIN32)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/interfaces
)
