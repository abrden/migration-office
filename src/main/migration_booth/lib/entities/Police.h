#ifndef MIGRATION_OFFICE_POLICE_H
#define MIGRATION_OFFICE_POLICE_H

#include "AlertData.h"
#include "Resident.h"
#include "Foreigner.h"
#include "FifoReader.h"
#include "FifoWriter.h"
#include "ExclusiveLock.h"
#include "Logger.h"
#include "WantedPersonAlert.h"
#include "AlertsSharedMemory.h"
#include "BoothsWithUnreadFugitives.h"

#include <vector>

class Police {

    private:
        Logger& logger;

        FifoReader fugitives_fifo;
        ExclusiveLock fugitives_fifo_lock;
        ExclusiveLock alerts_lock;
        AlertsSharedMemory alerts_shm;
        BoothsWithUnreadFugitives booths;
        std::vector<unsigned int> fugitives;

        std::list<WantedPersonAlert*> alerts;

        size_t arrested_residents;
        size_t deported_foreigners;

        void destroy_alerts();
    public:
        explicit Police(Logger& logger);
        void receive_fugitives();
        void get_current_alerts();
        bool is_fugitive(Resident* resident);
        bool is_wanted_person(Foreigner* foreigner);
        void report(Resident* resident);
        void report(Foreigner* foreigner);
        ~Police();

};


#endif //MIGRATION_OFFICE_POLICE_H
