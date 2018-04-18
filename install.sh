#!/bin/bash

echo "==================== Creating build directory ===================="
rm -rf build
mkdir build && cd build
echo "==================== Done ===================="

echo "==================== Compiling project ===================="
cmake -DCMAKE_BUILD_TYPE=Release .. && make -j2
echo "==================== Done ===================="

echo "==================== Running tests ===================="
valgrind --leak-check=full\
         --show-leak-kinds=all\
         --trace-children=yes\
         --error-exitcode=1 --errors-for-leak-kinds=all\
         ./migration_office -p ../resources/people.txt\
         -a ../resources/alerts.txt\
         -f ../resources/fugitives.txt -b 4 -s 1