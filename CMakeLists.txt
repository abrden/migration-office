cmake_minimum_required(VERSION 2.8.12.2)
project(migration_office)

set(CMAKE_CXX_STANDARD 11)

#if(CMAKE_COMPILER_IS_GNUCXX)
#    # Errors and warnings.
#    set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -Wno-conversion -Wno-unused-parameter -Wextra -Wtype-limits -pedantic -pedantic-errors")
#    # Valgrind and debug
#    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} -O0 -ggdb3 -DDEBUG")
#    # Optimizing
#    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
#endif(CMAKE_COMPILER_IS_GNUCXX)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(src/main/)