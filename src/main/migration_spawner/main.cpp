#include <iostream>
#include <unistd.h>

#include "PeopleSpawner.h"

enum ARGUMENTS {
    PEOPLE_FILE_POS,
    DEBUG_POS,
    LOG_FILE_POS
};

int main(int argc, char* argv[]) {
    std::cout << "Welcome to the Conculandia Migration Spawner " << getpid() << "!" << std::endl;
    std::cout << "people file = " << argv[ARGUMENTS::PEOPLE_FILE_POS] << std::endl;
    std::cout << "debug = " << argv[ARGUMENTS::DEBUG_POS] << std::endl;
    std::cout << "log file = " << argv[ARGUMENTS::LOG_FILE_POS] << std::endl;

    PeopleSpawner spawner(argv[ARGUMENTS::PEOPLE_FILE_POS], std::stoi(argv[ARGUMENTS::DEBUG_POS]), argv[ARGUMENTS::LOG_FILE_POS]);

    spawner.run();

    return 0;
}
