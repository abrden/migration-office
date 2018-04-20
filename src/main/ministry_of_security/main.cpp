#include <iostream>
#include <unistd.h>
#include "MinisterOfSecurity.h"

enum ARGUMENTS {
    ALERTS_FILE_POS = 1,
    FUGITIVES_FILE_POS,
    DEBUG_POS,
    LOG_FILE_POS,
    BOOTHS_NUMBER_POS
};

int main(int argc, char* argv[]) {
    MinisterOfSecurity ms(argv[ARGUMENTS::ALERTS_FILE_POS],
                          argv[ARGUMENTS::FUGITIVES_FILE_POS],
                          static_cast<size_t>(std::stoi(argv[ARGUMENTS::BOOTHS_NUMBER_POS])),
                          std::stoi(argv[ARGUMENTS::DEBUG_POS]),
                          argv[ARGUMENTS::LOG_FILE_POS]);
    ms.open();
    return 0;
}
