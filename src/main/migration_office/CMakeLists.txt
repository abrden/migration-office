project(migration_office)

add_subdirectory(lib)

set(SOURCES
        "main.cpp"
        "MigrationOffice.cpp"
        "MigrationOffice.h")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC concurrency)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC entities)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _definitions)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _migration_office_entities)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _migration_office_signal_handlers)