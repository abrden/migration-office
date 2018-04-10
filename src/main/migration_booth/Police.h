#ifndef MIGRATION_OFFICE_POLICE_H
#define MIGRATION_OFFICE_POLICE_H

#include "Resident.h"
#include "Foreigner.h"

class Police {

    public:
        bool is_fugitive(Resident* resident);
        bool is_wanted_person(Foreigner* foreigner);
        void report(Resident* resident);

};


#endif //MIGRATION_OFFICE_POLICE_H
