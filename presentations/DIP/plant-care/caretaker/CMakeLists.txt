project(caretaker)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCE
    ${PROJECT_SOURCE_DIR}/include/caretaker/AloeCaretaker.hpp
    ${PROJECT_SOURCE_DIR}/include/caretaker/CactusCaretaker.hpp
    ${PROJECT_SOURCE_DIR}/src/AloeCaretaker.cpp
    ${PROJECT_SOURCE_DIR}/src/CactusCaretaker.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE})
target_link_libraries(${PROJECT_NAME} sensors)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
