#include <iostream>

#include "MigrationBooth.h"

enum ARGUMENTS {
    DEBUG_POS = 1,
    LOG_FILE_POS
};

int main(int argc, char* argv[]) {
    MigrationBooth booth(std::stoi(argv[ARGUMENTS::DEBUG_POS]), argv[ARGUMENTS::LOG_FILE_POS]);
    booth.open();
    return 0;
}
