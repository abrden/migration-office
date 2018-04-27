#include <iostream>
#include <unistd.h>

#include "PeopleSpawner.h"

enum ARGUMENTS {
    PEOPLE_FILE_POS = 1,
    DEBUG_POS,
    LOG_FILE_POS
};

int main(int argc, char* argv[]) {
    PeopleSpawner spawner(argv[ARGUMENTS::PEOPLE_FILE_POS], std::stoi(argv[ARGUMENTS::DEBUG_POS]), argv[ARGUMENTS::LOG_FILE_POS]);

    spawner.run();

    return 0;
}
