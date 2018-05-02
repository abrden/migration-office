project(people_spawner)

set(SOURCES
        "main.cpp"
        "PeopleSpawner.cpp"
        "PeopleSpawner.h")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC concurrency)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC entities)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC configuration_file_reader)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _sigint_handler)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _signal_handler)
