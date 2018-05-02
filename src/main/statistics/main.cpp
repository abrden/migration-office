#include <iostream>
#include <map>
#include "Statistics.h"

enum ARGUMENTS {
    DEBUG_POS = 1,
    LOG_FILE_POS
};

int main(int argc, char* argv[]) {
    Statistics s(std::stoi(argv[ARGUMENTS::DEBUG_POS]), argv[ARGUMENTS::LOG_FILE_POS]);

    s.start();

    return 0;
}