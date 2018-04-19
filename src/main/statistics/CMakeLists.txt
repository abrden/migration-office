project(statistics)

set(SOURCES "main.cpp"
            "Statistics.cpp"
            "Statistics.h")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC concurrency)