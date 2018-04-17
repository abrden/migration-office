#include <iostream>
#include <unistd.h>

#include "MigrationBooth.h"

enum ARGUMENTS {
    DEBUG_POS = 1,
    LOG_FILE_POS
};

int main(int argc, char* argv[]) {
    std::cout << "Welcome to the Conculandia Migration Booth " << getpid() << "!" << std::endl;
    std::cout << "debug = " << argv[ARGUMENTS::DEBUG_POS] << std::endl;
    std::cout << "log file = " << argv[ARGUMENTS::LOG_FILE_POS] << std::endl;

    MigrationBooth booth(std::stoi(argv[ARGUMENTS::DEBUG_POS]), argv[ARGUMENTS::LOG_FILE_POS]);

    booth.open();

    return 0;
}
