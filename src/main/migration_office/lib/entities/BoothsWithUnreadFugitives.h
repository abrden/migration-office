#ifndef MIGRATION_OFFICE_BOOTHSWITHUNREADFUGITIVES_H
#define MIGRATION_OFFICE_BOOTHSWITHUNREADFUGITIVES_H

#include "Semaphore.h"

class BoothsWithUnreadFugitives {

    private:
        Semaphore booths;

    public:
        BoothsWithUnreadFugitives(const int booths_number);
        ~BoothsWithUnreadFugitives();
};

#endif //MIGRATION_OFFICE_BOOTHSWITHUNREADFUGITIVES_H
