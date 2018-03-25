project(tests)

file(GLOB SOURCES "*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/../main/*.cpp")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../main/main.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
include_directories(../main)
target_link_libraries(tests Catch)
ParseAndAddCatchTests(${PROJECT_NAME})

