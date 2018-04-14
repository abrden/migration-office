#ifndef MIGRATION_OFFICE_PEOPLESPAWNER_H
#define MIGRATION_OFFICE_PEOPLESPAWNER_H

#include <string>

#include "Spawnables.h"
#include "Spawner.h"
#include "SIGINTHandler.h"

class PeopleSpawner {

    private:
        const std::string people_file;
        const bool debug;
        const std::string log_file;

        SIGINTHandler sigint_handler;
        Spawnables people;
        Spawner spawner;

    public:
        PeopleSpawner(const std::string& people_file, const bool debug, const std::string& log_file);
        void start();
        ~PeopleSpawner();

};


#endif //MIGRATION_OFFICE_PEOPLESPAWNER_H
