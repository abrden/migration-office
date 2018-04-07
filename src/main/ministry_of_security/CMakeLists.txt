project(ministry_of_security)

file(GLOB SOURCES "*.cpp")

add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC common)