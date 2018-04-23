#include "SIGUSRHandler.h"

#include <assert.h>

SIGUSRHandler::SIGUSRHandler() : news_available(0) {}

SIGUSRHandler::~SIGUSRHandler() = default;

int SIGUSRHandler::handle_signal(int signum) {
    assert(signum == SIGUSR1);
    news_available = 1;
    return 0;
}

sig_atomic_t SIGUSRHandler::get_news_available() const {
    return news_available;
}

void SIGUSRHandler::reset() {
    news_available = 0;
}