project(migration_office)

file(GLOB SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC rest)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC concurrency)