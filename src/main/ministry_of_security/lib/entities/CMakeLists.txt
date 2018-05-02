project(_ministry_of_security_entities)

file(GLOB SOURCES "*.cpp" "*.h")

add_library(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC entities)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC concurrency)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC configuration_file_reader)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _sigint_handler)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _signal_handler)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _definitions)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})