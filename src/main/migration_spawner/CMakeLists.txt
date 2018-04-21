project(migration_spawner)

add_subdirectory(lib)

set(SOURCES
        "main.cpp"
        "PeopleSpawner.cpp"
        "PeopleSpawner.h")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC rest)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC concurrency)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _signal_handlers)