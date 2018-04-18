project(tests)

file(GLOB SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC entities)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC rest)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _migration_booth_entities)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC Catch)
ParseAndAddCatchTests(${PROJECT_NAME})

