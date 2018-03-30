#ifndef MIGRATION_OFFICE_MINISTEROFSECURITY_H
#define MIGRATION_OFFICE_MINISTEROFSECURITY_H

#include "WantedPersonAlert.h"

class MinisterOfSecurity {

    private:
        std::list<WantedPersonAlert*> alerts;

    public:
        MinisterOfSecurity(const std::string& alerts_file_path);
        ~MinisterOfSecurity();

};


#endif //MIGRATION_OFFICE_MINISTEROFSECURITY_H
