project(tests)

file(GLOB SOURCES "*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(tests Catch)
ParseAndAddCatchTests(${PROJECT_NAME})

