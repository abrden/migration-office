#include <iostream>
#include <unistd.h>

#include "MigrationBooth.h"

enum ARGUMENTS {
    PEOPLE_FILE_POS = 1,
    ALERTS_FILE_POS,
    FUGITIVES_FILE_POS,
    DEBUG_POS,
    LOG_FILE_POS
};

int main(int argc, char* argv[]) {
//    std::cout << "Welcome to the Conculandia Migration Booth " << getpid() << "!" << std::endl;
//    std::cout << "people file = " << argv[ARGUMENTS::PEOPLE_FILE_POS] << std::endl;
//    std::cout << "alerts file = " << argv[ARGUMENTS::ALERTS_FILE_POS] << std::endl;
//    std::cout << "fugitives file = " << argv[ARGUMENTS::FUGITIVES_FILE_POS] << std::endl;
//    std::cout << "debug = " << argv[ARGUMENTS::DEBUG_POS] << std::endl;
//    std::cout << "log file = " << argv[ARGUMENTS::LOG_FILE_POS] << std::endl;

    MigrationBooth booth(argv[ARGUMENTS::PEOPLE_FILE_POS], argv[ARGUMENTS::ALERTS_FILE_POS], argv[ARGUMENTS::FUGITIVES_FILE_POS],
                         std::stoi(argv[ARGUMENTS::DEBUG_POS]), argv[ARGUMENTS::LOG_FILE_POS]);

    booth.open();

    return 0;
}
