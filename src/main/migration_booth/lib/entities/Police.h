#ifndef MIGRATION_OFFICE_POLICE_H
#define MIGRATION_OFFICE_POLICE_H

#include "Resident.h"
#include "Foreigner.h"
#include "FifoReader.h"
#include "FifoWriter.h"
#include "ExclusiveLock.h"
#include "Logger.h"

#include <vector>
#include "WantedPersonAlert.h"

class Police {

    private:
        Logger& logger;

        FifoReader fugitives_fifo;
        FifoWriter ministry_fifo;
        ExclusiveLock fugitives_fifo_lock;
        std::vector<unsigned int> fugitives;
        void receive_fugitives();

        std::list<WantedPersonAlert*> alerts;
        void receive_alert();

        size_t arrested_residents;
        size_t deported_foreigners;

    public:
        explicit Police(Logger& logger);
        bool is_fugitive(Resident* resident);
        bool is_wanted_person(Foreigner* foreigner);
        void report(Resident* resident);
        void report(Foreigner* foreigner);

};


#endif //MIGRATION_OFFICE_POLICE_H
