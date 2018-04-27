#include "AlertDeleter.h"

enum ARGUMENTS {
    ALERTS_FILE_POS = 1,
    DEBUG_POS,
    LOG_FILE_POS
};

int main(int argc, char* argv[]) {
    AlertDeleter ad(argv[ARGUMENTS::ALERTS_FILE_POS], std::stoi(argv[ARGUMENTS::DEBUG_POS]), argv[ARGUMENTS::LOG_FILE_POS]);

    ad.run();

    return 0;
}

