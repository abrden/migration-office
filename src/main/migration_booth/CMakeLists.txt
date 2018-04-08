project(migration_booth)

file(GLOB SOURCES "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES} MigrationBooth.cpp MigrationBooth.h)