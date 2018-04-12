project(migration_booth)

add_subdirectory(lib)

file(GLOB SOURCES "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _migration_booth)