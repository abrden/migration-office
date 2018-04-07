#!/bin/bash

echo "==================== Creating build directory ===================="
rm -rf build
mkdir build && cd build
echo "==================== Done ===================="

echo "==================== Compiling project ===================="
NUMCPUS=`grep -c '^processor' /proc/cpuinfo`
cmake .. && make -j$NUMCPUS
echo "==================== Done ===================="

echo "==================== Running tests ===================="
valgrind --leak-check=full\
         --show-leak-kinds=all\
         --trace-children=yes\
         --error-exitcode=1 --errors-for-leak-kinds=all ./tests