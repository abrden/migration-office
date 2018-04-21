#include <iostream>
#include <map>
#include "Statistics.h"

enum ARGUMENTS {
    DEBUG_POS = 1,
    LOG_FILE_POS,
    BOOTHS_NUMBER_POS
};

int main(int argc, char* argv[]) {
    Statistics s(static_cast<size_t>(std::stoi(argv[ARGUMENTS::BOOTHS_NUMBER_POS])),
                 std::stoi(argv[ARGUMENTS::DEBUG_POS]), argv[ARGUMENTS::LOG_FILE_POS]);

    s.start();

    return 0;
}