project(tests)

file(GLOB SOURCES "*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/../main/old_main/*.cpp")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../main/old_main/main.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
include_directories(../main/old_main)
target_link_libraries(tests Catch)
ParseAndAddCatchTests(${PROJECT_NAME})

