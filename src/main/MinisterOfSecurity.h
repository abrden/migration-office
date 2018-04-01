#ifndef MIGRATION_OFFICE_MINISTEROFSECURITY_H
#define MIGRATION_OFFICE_MINISTEROFSECURITY_H

#include "WantedPersonAlert.h"
#include "Spawner.h"

class MinisterOfSecurity {

    private:
        std::list<std::pair<int, WantedPersonAlert*>> alarms;
        std::list<std::pair<int, WantedPersonAlert*>> load_alarms(const std::string& file_path);

    public:
        explicit MinisterOfSecurity(const std::string& alerts_file_path);
        ~MinisterOfSecurity();

};


#endif //MIGRATION_OFFICE_MINISTEROFSECURITY_H
