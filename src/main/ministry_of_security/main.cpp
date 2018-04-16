#include <iostream>
#include <unistd.h>
#include "MinisterOfSecurity.h"

enum ARGUMENTS {
    ALERTS_FILE_POS,
    FUGITIVES_FILE_POS,
    DEBUG_POS,
    LOG_FILE_POS,
    BOOTHS_NUMBER_POS
};

int main(int argc, char* argv[]) {
    std::cout << "Welcome to the Conculandia Ministry of Security " << getpid() << "!" << std::endl;
    std::cout << "alerts file = " << argv[ARGUMENTS::ALERTS_FILE_POS] << std::endl;
    std::cout << "fugitives file = " << argv[ARGUMENTS::FUGITIVES_FILE_POS] << std::endl;
    std::cout << "debug = " << argv[ARGUMENTS::DEBUG_POS] << std::endl;
    std::cout << "log file = " << argv[ARGUMENTS::LOG_FILE_POS] << std::endl;
    std::cout << "booths_number = " << argv[ARGUMENTS::BOOTHS_NUMBER_POS] << std::endl;

    MinisterOfSecurity ms(argv[ARGUMENTS::ALERTS_FILE_POS],
                          argv[ARGUMENTS::FUGITIVES_FILE_POS],
                          static_cast<size_t>(std::stoi(argv[ARGUMENTS::BOOTHS_NUMBER_POS])));
    ms.send_fugitives();
    sleep(4); // FIXME sleep to give time for booths to finish reading fugitives
    return 0;
}
