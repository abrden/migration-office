#ifndef MIGRATION_OFFICE_POLICE_H
#define MIGRATION_OFFICE_POLICE_H

#include "SharedMemory.h"
#include "Resident.h"
#include "Foreigner.h"

#include <vector>

class Police {

    private:
        SharedMemory<std::vector<unsigned int>> sm;
        std::vector<unsigned int> fugitives;
    public:
        Police();
        bool is_fugitive(Resident* resident);
        bool is_wanted_person(Foreigner* foreigner);
        void report(Resident* resident);

};


#endif //MIGRATION_OFFICE_POLICE_H
