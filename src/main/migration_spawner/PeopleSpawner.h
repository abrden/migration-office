#ifndef MIGRATION_OFFICE_PEOPLESPAWNER_H
#define MIGRATION_OFFICE_PEOPLESPAWNER_H

#include <string>

#include "Spawnables.h"
#include "Spawner.h"
#include "FifoWriter.h"
#include "SIGINTHandler.h"

class PeopleSpawner : public Spawner {

    private:
        const std::string people_file;
        const bool debug;
        const std::string log_file;

        SIGINTHandler sigint_handler;
        Spawnables people;
        FifoWriter fifo;

    public:
        PeopleSpawner(const std::string& people_file, const bool debug, const std::string& log_file);
        void spawn(Spawnable* spawnable) override;
        bool quit() override;
        ~PeopleSpawner() override;

};


#endif //MIGRATION_OFFICE_PEOPLESPAWNER_H
