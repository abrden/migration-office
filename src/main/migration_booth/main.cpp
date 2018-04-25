#include <iostream>
#include <unistd.h>

#include "MigrationBooth.h"

enum ARGUMENTS {
    STAMPERS_NUMBER_POS = 1,
    DEBUG_POS ,
    LOG_FILE_POS
};

int main(int argc, char* argv[]) {
    MigrationBooth booth(std::stoi(argv[ARGUMENTS::STAMPERS_NUMBER_POS]),
                         std::stoi(argv[ARGUMENTS::DEBUG_POS]),
                         argv[ARGUMENTS::LOG_FILE_POS]);

    booth.open();

    return 0;
}
