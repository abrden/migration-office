#ifndef MIGRATION_OFFICE_MINISTEROFSECURITY_H
#define MIGRATION_OFFICE_MINISTEROFSECURITY_H

#include "WantedPersonAlert.h"
#include "Spawner.h"

class MinisterOfSecurity {

    private:
        std::list<std::pair<int, WantedPersonAlert*>> alerts;
        std::list<std::pair<int, WantedPersonAlert*>> load_alarms(const std::string& file_path);

    public:
        explicit MinisterOfSecurity(const std::string& alerts_file_path);
        std::list<std::pair<int, WantedPersonAlert*>>& get_alerts();
        ~MinisterOfSecurity();

};


#endif //MIGRATION_OFFICE_MINISTEROFSECURITY_H
