#include "SIGINTHandler.h"

SIGINTHandler::SIGINTHandler() : graceful_quit(0) {}

SIGINTHandler::~SIGINTHandler() {}

int SIGINTHandler::handle_signal(int signum) {
    assert(signum == SIGINT);
    graceful_quit = 1;
    return 0;
}

sig_atomic_t SIGINTHandler::get_graceful_quit() const {
    return graceful_quit;
}