project(alert_deleter)

set(SOURCES "main.cpp"
        "AlertDeleter.cpp"
        "AlertDeleter.h")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC concurrency)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC configuration_file_reader)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _definitions)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _sigint_handler)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _signal_handler)