#ifndef MIGRATION_OFFICE_BOOTHSWITHUNREADFUGITIVES_H
#define MIGRATION_OFFICE_BOOTHSWITHUNREADFUGITIVES_H

#include "Semaphore.h"

class BoothsWithUnreadFugitives {

    private:
        Semaphore booths;

    public:
        BoothsWithUnreadFugitives();
        void notify_read_fugitives();
};

#endif //MIGRATION_OFFICE_BOOTHSWITHUNREADFUGITIVES_H
