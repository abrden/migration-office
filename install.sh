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
         ./tests

test_return=$?
echo "==================== Done ===================="
echo "==================== Running project ===================="
valgrind --leak-check=full\
         --show-leak-kinds=all\
         --trace-children=yes\
         --error-exitcode=1 --errors-for-leak-kinds=all\
         ./migration_office -p ../resources/people.txt\
         -a ../resources/alerts.txt\
         -f ../resources/fugitives.txt -b 4 -s 1 -d < input.txt

project_return=$?

if (($test_return == 1 || $project_return == 1)); then
    exit -1
else
    exit 0
fi

