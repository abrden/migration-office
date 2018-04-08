project(ministry_of_security)

add_subdirectory(lib)

set(SOURCES "main.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC rest)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ministry_of_security_lib)