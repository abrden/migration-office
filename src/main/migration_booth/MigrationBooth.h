#ifndef MIGRATION_OFFICE_MIGRATIONBOOTH_H
#define MIGRATION_OFFICE_MIGRATIONBOOTH_H

#include "Person.h"
#include "Resident.h"
#include "Foreigner.h"
#include "SIGINTHandler.h"
#include "SIGUSRHandler.h"
#include "PersonsQueue.h"
#include "Stampers.h"
#include "Police.h"
#include "StatisticsCommunicator.h"
#include "Logger.h"
#include "Semaphore.h"

#include <string>

class MigrationBooth {

    private:
        Logger logger;

        SIGINTHandler sigint_handler;
        PersonsQueue queue;
        Police police;
        Stampers stampers;
        StatisticsCommunicator statistics_communicator;

        void attend_resident(Resident* resident);
        void attend_foreigner(Foreigner* foreigner);

    public:
        MigrationBooth(const int stampers_numer, const bool debug, const std::string log_file);
        void open();
        ~MigrationBooth();

};


#endif //MIGRATION_OFFICE_MIGRATIONBOOTH_H
