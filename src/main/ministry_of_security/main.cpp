#include <iostream>
#include "MinisterOfSecurity.h"

enum ARGUMENTS {
    ALERTS_FILE_POS = 1,
    FUGITIVES_FILE_POS,
    DEBUG_POS,
    LOG_FILE_POS,
    BOOTHS_NUMBER_POS,
    FIRST_BOOTH_PID_POS
};

int main(int argc, char* argv[]) {
    std::vector<pid_t> booths_ids;
    size_t booths_number = static_cast<size_t>(std::stoi(argv[ARGUMENTS::BOOTHS_NUMBER_POS]));
    for (size_t i = 0; i < booths_number; i++) {
        booths_ids.push_back(static_cast<pid_t>(std::stoi(argv[ARGUMENTS::FIRST_BOOTH_PID_POS + i])));
    }
    MinisterOfSecurity ms(argv[ARGUMENTS::ALERTS_FILE_POS],
                          argv[ARGUMENTS::FUGITIVES_FILE_POS],
                          booths_number,
                          std::stoi(argv[ARGUMENTS::DEBUG_POS]),
                          argv[ARGUMENTS::LOG_FILE_POS]);
    ms.open();
    return 0;
}
