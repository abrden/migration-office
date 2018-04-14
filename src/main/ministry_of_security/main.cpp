#include <iostream>
#include <unistd.h>

enum ARGUMENTS {
    ALERTS_FILE_POS,
    FUGITIVES_FILE_POS,
    DEBUG_POS,
    LOG_FILE_POS
};

int main(int argc, char* argv[]) {
    std::cout << "Welcome to the Conculandia Ministry of Security " << getpid() << "!" << std::endl;
    std::cout << "alerts file = " << argv[ARGUMENTS::ALERTS_FILE_POS] << std::endl;
    std::cout << "fugitives file = " << argv[ARGUMENTS::FUGITIVES_FILE_POS] << std::endl;
    std::cout << "debug = " << argv[ARGUMENTS::DEBUG_POS] << std::endl;
    std::cout << "log file = " << argv[ARGUMENTS::LOG_FILE_POS] << std::endl;
    return 0;
}
