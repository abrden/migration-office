project(migration_booth)

add_subdirectory(lib)

set(SOURCES
        "main.cpp"
        "MigrationBooth.cpp"
        "MigrationBooth.h")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _migration_booth_entities)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _sigint_handler)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _signal_handler)