#ifndef MIGRATION_OFFICE_BOOTHSWITHUNREADFUGITIVES_H
#define MIGRATION_OFFICE_BOOTHSWITHUNREADFUGITIVES_H

#include "Semaphore.h"

class BoothsWithUnreadFugitives {

    private:
        Semaphore booths;

    public:
        BoothsWithUnreadFugitives();
        void wait_for_booths_to_read();
};

#endif //MIGRATION_OFFICE_BOOTHSWITHUNREADFUGITIVES_H
