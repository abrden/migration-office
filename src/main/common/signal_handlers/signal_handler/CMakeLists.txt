project(_signal_handler)

file(GLOB SOURCES "*.cpp" "*.h")

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})