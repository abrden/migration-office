#ifndef MIGRATION_OFFICE_MIGRATIONBOOTH_H
#define MIGRATION_OFFICE_MIGRATIONBOOTH_H

#include "Person.h"
#include "Resident.h"
#include "Foreigner.h"
#include "SIGINTHandler.h"
#include "PersonsQueue.h"
#include "Stampers.h"
#include "Police.h"

#include <string>

class MigrationBooth {

    private:
        const std::string people_file, alerts_file, fugitives_file;
        const bool debug;
        const std::string log_file;

        SIGINTHandler sigint_handler;
        PersonsQueue queue;
        Stampers stampers;
        Police police;

        void attend_resident(Resident* resident);
        void attend_foreigner(Foreigner* foreigner);

        // Do we need this?
        std::list<Resident*> arrived_residents;
        std::list<Foreigner*> arrived_foreigners;

    public:
        MigrationBooth(const std::string people_file, const std::string alerts_file, const std::string fugitives_file,
                       const bool debug, const std::string log_file);
        void open();

};


#endif //MIGRATION_OFFICE_MIGRATIONBOOTH_H
