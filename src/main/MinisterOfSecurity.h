#ifndef MIGRATION_OFFICE_MINISTEROFSECURITY_H
#define MIGRATION_OFFICE_MINISTEROFSECURITY_H

#include "WantedPersonAlert.h"
#include "Spawner.h"

class MinisterOfSecurity : public Spawner {

    public:
        explicit MinisterOfSecurity(const std::string& alerts_file_path);
        std::list<std::pair<int, Spawnable*>> load_items(const std::string& file_path);
        ~MinisterOfSecurity();

};


#endif //MIGRATION_OFFICE_MINISTEROFSECURITY_H
