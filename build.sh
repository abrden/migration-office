#!/bin/bash

echo "==================== Creating build directory ===================="
rm -rf build
mkdir build && cd build
echo "==================== Done ===================="

echo "==================== Compiling project ===================="
cmake -DCMAKE_BUILD_TYPE=Release .. && make -j4
echo "==================== Done ===================="