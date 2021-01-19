project(Common)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set(HEADERS
    ${PROJECT_SOURCE_DIR}/include/constants/Constants.hpp
    ${PROJECT_SOURCE_DIR}/include/types/User.hpp
    ${PROJECT_SOURCE_DIR}/include/types/Report.hpp
    ${PROJECT_SOURCE_DIR}/include/types/ReportFormat.hpp
)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/types/User.cpp
    ${PROJECT_SOURCE_DIR}/src/types/Report.cpp
    ${PROJECT_SOURCE_DIR}/src/types/ReportFormat.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
