#!/bin/bash

echo "==================== Creating build directory ===================="
mkdir -p build && cd build
echo "==================== Done ===================="

echo "==================== Compiling project ===================="
cmake .. && make
echo "==================== Done ===================="

echo "==================== Running tests ===================="
valgrind --leak-check=full\
         --show-leak-kinds=all\
         --trace-children=yes\
         --error-exitcode=1 --errors-for-leak-kinds=all ./tests
echo "Valgrind exit code" $?
echo "==================== Done ===================="
exit $?