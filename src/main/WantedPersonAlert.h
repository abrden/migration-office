#ifndef MIGRATION_OFFICE_WANTEDPERSONALERT_H
#define MIGRATION_OFFICE_WANTEDPERSONALERT_H

#include <list>
#include "Feature.h"

class WantedPersonAlert {

    private:
        const int timestamp;
        std::list<Feature*> person_features;

    public:
        WantedPersonAlert(const int timestamp, const std::list<Feature*>& person_features);
        const std::list<Feature*> get_features();
        int get_timestamp() const;
        ~WantedPersonAlert();

};


#endif //MIGRATION_OFFICE_WANTEDPERSONALERT_H
