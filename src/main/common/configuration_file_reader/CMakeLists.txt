project(configuration_file_reader)

file(GLOB SOURCES "*.h" "*.cpp")

add_library(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC entities)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})