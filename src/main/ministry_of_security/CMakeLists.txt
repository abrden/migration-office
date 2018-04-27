project(ministry_of_security)

add_subdirectory(lib)

set(SOURCES "main.cpp"
            "MinisterOfSecurity.cpp"
            "MinisterOfSecurity.h")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC concurrency)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC entities)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _signal_handlers)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _ministry_of_security_entities)