#ifndef MIGRATION_OFFICE_MINISTEROFSECURITY_H
#define MIGRATION_OFFICE_MINISTEROFSECURITY_H

#include "WantedPersonAlert.h"
#include "Spawner.h"
#include "SharedMemory.h"

#include <vector>

class MinisterOfSecurity {

    private:
        SharedMemory<std::vector<unsigned int>> sm;
        Spawnables alerts;
        std::vector<unsigned int> fugitives;

    public:
        MinisterOfSecurity(const std::string& alerts_file_path, const std::string& fugitives_file_path);
        void send_fugitives();
        Spawnables& get_alerts();
        ~MinisterOfSecurity() = default;

};


#endif //MIGRATION_OFFICE_MINISTEROFSECURITY_H
