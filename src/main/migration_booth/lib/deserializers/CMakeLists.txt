project(_migration_booth_deserializers)

file(GLOB SOURCES "*.h" "*.cpp")

add_library(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC entities)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC configuration_file_reader)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _migration_booth_entities)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})