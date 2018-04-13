#include "SIGINTHandler.h"

#include <assert.h>
#include <signal.h>
#include <iostream>

SIGINTHandler::SIGINTHandler() {}

SIGINTHandler::~SIGINTHandler() = default;

int SIGINTHandler::handle_signal(int signum) {
    assert(signum == SIGINT);
    std::cout << "I'm waiting for my booths to close" << std::endl;
    return 0;
}