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
         ./migration_office -p ../resources/gen_people.txt\
         -a ../resources/gen_alerts.txt\
         -f ../resources/gen_fugitives.txt -b 5 -s 3 -d
