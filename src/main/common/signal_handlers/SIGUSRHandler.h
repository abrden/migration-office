#ifndef MIGRATION_OFFICE_SIGUSRHANDLER_H
#define MIGRATION_OFFICE_SIGUSRHANDLER_H

#include "EventHandler.h"

#include <csignal>

class SIGUSRHandler : public EventHandler {

    private:
        sig_atomic_t news_available;

    public:
        SIGUSRHandler();
        ~SIGUSRHandler() override;
        int handle_signal(int signum) override;
        sig_atomic_t get_news_available() const;
        void reset();

};


#endif //MIGRATION_OFFICE_SIGUSRHANDLER_H
