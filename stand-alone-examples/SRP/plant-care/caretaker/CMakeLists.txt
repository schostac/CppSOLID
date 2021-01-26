project(caretaker)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCE
    ${PROJECT_SOURCE_DIR}/include/caretaker/PlantCaretaker.hpp
    ${PROJECT_SOURCE_DIR}/src/PlantCaretaker.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
