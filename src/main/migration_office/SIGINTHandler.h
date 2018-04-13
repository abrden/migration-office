#ifndef MIGRATION_OFFICE_SIGINTHANDLER_H
#define MIGRATION_OFFICE_SIGINTHANDLER_H

#include "EventHandler.h"

class SIGINTHandler : public EventHandler {

    public:
        SIGINTHandler();
        ~SIGINTHandler();
        virtual int handle_signal(int signum) override;

};


#endif //MIGRATION_OFFICE_SIGINTHANDLER_H
