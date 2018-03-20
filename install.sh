#!/bin/bash

echo "Running project"

valgrind --leak-check=full\
         --show-leak-kinds=all\
         --trace-children=yes\
         --error-exitcode=1 --errors-for-leak-kinds=all ./src/main/main
echo $?
exit $?