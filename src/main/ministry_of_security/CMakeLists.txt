project(minister_of_security)

file(GLOB SOURCES "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})