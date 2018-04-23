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
#include "SharedMemory.h"

#include <vector>

class Police {

    private:
        Logger& logger;

        FifoReader fugitives_fifo;
        FifoWriter ministry_fifo;
        ExclusiveLock fugitives_fifo_lock;
        ExclusiveLock alerts_lock;
        SharedMemory<AlertData> alerts_shm;
        std::vector<unsigned int> fugitives;
        FifoWriter alerts_fifo;
        void receive_fugitives();

        std::list<WantedPersonAlert*> alerts;

        size_t arrested_residents;
        size_t deported_foreigners;

    public:
        explicit Police(Logger& logger);
        void receive_alert();
        bool is_fugitive(Resident* resident);
        bool is_wanted_person(Foreigner* foreigner);
        void report(Resident* resident);
        void report(Foreigner* foreigner);

};


#endif //MIGRATION_OFFICE_POLICE_H
