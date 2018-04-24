#!/bin/bash

cd build
echo "==================== Running tests and project ===================="
valgrind --suppressions=../vg.supp --leak-check=full\
         --show-leak-kinds=all\
         --trace-children=yes\
         --error-exitcode=1 --errors-for-leak-kinds=all\
         ./tests && \
         echo "exit" | valgrind --suppressions=../vg.supp\
         --leak-check=full\
         --show-leak-kinds=all\
         --trace-children=yes\
         --error-exitcode=1 --errors-for-leak-kinds=all\
         ./migration_office -p ../resources/people.txt\
         -a ../resources/alerts.txt\
         -f ../resources/fugitives.txt -b 4 -s 1 -d
